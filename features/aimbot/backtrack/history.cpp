#include "history.h"

//https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/sp/src/game/server/gameinterface.cpp#L2802
float history::get_lerp_time()
{
	static c_con_var* sv_minupdaterate = interfaces::cvar->find_var("sv_minupdaterate");
	static c_con_var* sv_maxupdaterate = interfaces::cvar->find_var("sv_maxupdaterate");
	static c_con_var* cl_updaterate = interfaces::cvar->find_var("cl_updaterate");
	static c_con_var* cl_interpolate = interfaces::cvar->find_var("cl_interpolate");
	static c_con_var* cl_interp_ratio = interfaces::cvar->find_var("cl_interp_ratio");
	static c_con_var* cl_interp = interfaces::cvar->find_var("cl_interp");
	static c_con_var* sv_client_min_interp_ratio = interfaces::cvar->find_var("sv_client_min_interp_ratio");
	static c_con_var* sv_client_max_interp_ratio = interfaces::cvar->find_var("sv_client_max_interp_ratio");

	float lerp_time = 0.f;

	if (cl_interpolate->get_int() != 0)
	{
		int update_rate = std::clamp(cl_updaterate->get_int(), (int)sv_minupdaterate->get_float(), (int)sv_maxupdaterate->get_float());

		float lerp_ratio = cl_interp_ratio->get_float();
		if (lerp_ratio == 0)
			lerp_ratio = 1.f;

		float lerp_amount = cl_interp->get_float();

		if (sv_client_min_interp_ratio && sv_client_max_interp_ratio && sv_client_min_interp_ratio->get_float() != -1.f)
		{
			lerp_ratio = std::clamp(lerp_ratio, sv_client_min_interp_ratio->get_float(), sv_client_max_interp_ratio->get_float());
		}
		else
		{
			if (lerp_ratio == 0.f)
				lerp_ratio = 1.f;
		}

		lerp_time = max(lerp_amount, lerp_ratio / update_rate);
	}

	return lerp_time;
}

int history::estimate_server_arrive_tick()
{
	int tick = interfaces::global_vars->tick_count + 1;

	c_net_channel* net_channel = interfaces::engine->get_net_channel_info();
	if (net_channel)
		tick += utilities::time_to_ticks(net_channel->get_latency(1) + net_channel->get_latency(0));

	return tick;
}

bool history::is_delta_too_big(const c_vector& from, const c_vector& to)
{
	return (from - to).length_sqr() > 1600000.f;
}

bool history::can_restore_to_simulation_time(float simulation_time, bool* need_to_adjust_interp)
{
	float correct = get_lerp_time();

	c_net_channel* net_channel = interfaces::engine->get_net_channel_info();
	if (net_channel)
		correct += net_channel->get_latency(0);

	if (correct >= 1.f)
		return false;

	correct = std::clamp(correct, 0.0f, 1.0f);

	float diff = utilities::ticks_to_time(estimate_server_arrive_tick() - utilities::time_to_ticks(simulation_time));
	if (diff >= 1.f)
		return false;

	int target_tick = utilities::time_to_ticks(simulation_time);
	float delta_time = correct - utilities::ticks_to_time(estimate_server_arrive_tick() - target_tick);

	if (fabsf(delta_time) > 0.2f)
	{
		if (diff >= 0.f)
		{
			if (need_to_adjust_interp != nullptr)
				*need_to_adjust_interp = true;

			return true;
		}

		return false;
	}

	if (need_to_adjust_interp != nullptr)
		*need_to_adjust_interp = false;

	return true;
}

bool history::get_latest_record(int index, lag_record& out_record)
{
	c_base_entity* entity = interfaces::entity_list->get_entity(index);
	if (!entity || !entity->is_player())
		return false;

	auto& track = records[index - 1];
	if (track.empty())
		return false;

	bool record_found = false;
	c_vector prev_origin = entity->get_abs_origin();

	for (const auto& record : track)
	{
		if (is_delta_too_big(record.origin, prev_origin))
			break;

		if (!can_restore_to_simulation_time(record.simulation_time))
			break;

		float delta = utilities::ticks_to_time(interfaces::global_vars->tick_count) - record.arrive_time;
		if (delta > settings::aimbot::accuracy::backtrack)
			break;

		out_record = record;
		prev_origin = record.origin;

		record_found = true;
	}

	return record_found;
}

void history::update()
{
	if (interfaces::global_vars->max_clients <= 1)
		return records.clear();

	for (size_t i = 1; i <= interfaces::entity_list->get_highest_entity_index(); i++)
	{
		c_base_entity* entity = interfaces::entity_list->get_entity(i);

		if (!entity || !entity->is_player())
			continue;

		if (i == interfaces::engine->get_local_player())
			continue;

		auto& track = records[i - 1];

		if (!entity->is_alive())
		{
			if (!track.empty())
				track.clear();

			continue;
		}

		track.erase(std::remove_if(track.begin(), track.end(), 
		[](const lag_record& r) 
		{ 
			return utilities::ticks_to_time(interfaces::global_vars->tick_count) - r.simulation_time > 1.f; 
		}), track.end());

		lag_record record;
		record.arrive_time = utilities::ticks_to_time(estimate_server_arrive_tick());
		record.simulation_time = entity->get_simulation_time();
		record.origin = entity->get_abs_origin();

		void* model = entity->get_client_renderable()->get_model();
		if (!model)
			continue;

		studiohdr_t* hdr = interfaces::model_info->get_studio_model(model);
		if (!hdr)
			continue;

		record.bone_to_world.reset(new matrix3x4[hdr->num_bones]);

		entity->invalidate_bone_cache();
		if (!entity->get_client_renderable()->setup_bones(record.bone_to_world.get(), hdr->num_bones, BONE_USED_BY_ANYTHING, interfaces::global_vars->curtime))
			continue;

		track.insert(track.begin(), record);
	}
}