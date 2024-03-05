#include "history.h"

//https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/sp/src/game/server/gameinterface.cpp#L2802
/*float history::get_lerp_time()
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
}*/

/*float history::get_lowest_possible_lerp_time(int* update_rate)
{
	static c_con_var* sv_maxupdaterate = interfaces::cvar->find_var("sv_maxupdaterate");

	if (update_rate)
		*update_rate = sv_maxupdaterate->get_int();

	return 1.f / sv_maxupdaterate->get_int();
}*/

int history::estimate_server_arrive_tick()
{
	int tick = interfaces::global_vars->tick_count + 1;

	c_net_channel* net_channel = interfaces::engine->get_net_channel_info();
	if (net_channel)
		tick += utilities::time_to_ticks(net_channel->get_latency(1) + net_channel->get_latency(0));

	return tick;
}

bool history::can_restore_to_simulation_time(float simulation_time, bool* need_to_adjust_interp)
{
	float correct = 0.f;

	c_net_channel* net_channel = interfaces::engine->get_net_channel_info();
	if (net_channel)
		correct += net_channel->get_latency(0);

	int lerp_ticks = 0;

	correct += utilities::ticks_to_time(utilities::time_to_ticks(lerp_ticks));

	if (correct >= 1.f)
	{
		return false;
	}
	else if (correct < 0.f)
	{
		correct = 0.f;
	}

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

bool history::is_delta_too_big(const c_vector& from, const c_vector& to)
{
	return (from - to).length_sqr() > 1600000.f;
}

void history::get_usable_records_for_entity(c_base_entity* entity, std::vector<snapshot*>* out_records, float min_time, float max_time, bool* should_lag_fix)
{
	get_usable_records_for_index(entity->get_client_networkable()->get_index(), out_records, min_time, max_time, should_lag_fix);
}

void history::get_usable_records_for_index(int index, std::vector<snapshot*>* out_records, float min_time, float max_time, bool* should_lag_fix)
{
	std::vector<node*>& list = snapshots[index];
	if (list.size() == 0)
		return;
	 
	node* node = list.back();

	c_vector* prev_origin = &node->record->vec_origin;

	bool first_record_valid = false;
	if (list.size() >= 2)
	{
		if (can_restore_to_simulation_time(node->record->simulation_time))
		{
			first_record_valid = !is_delta_too_big(*prev_origin, node->prev->record->vec_origin);
		}
	}

	while (node != nullptr)
	{
		auto prev = node->prev;

		if (max_time != -1.f)
		{
			if (min_time == -1.f)
			{
				min_time = 0.f;
			}

			static c_con_var* cl_updaterate = interfaces::cvar->find_var("cl_updaterate");

			float snapshot_interval = 1.f / cl_updaterate->get_float();

			float delta = utilities::ticks_to_time(interfaces::global_vars->tick_count) - node->record->arrive_time;

			if (delta < min_time)
			{
				if (is_delta_too_big(*prev_origin, node->record->vec_origin))
				{
					if (first_record_valid)
						out_records->push_back(list.back()->record);

					if (should_lag_fix != nullptr)
						*should_lag_fix = !first_record_valid;

					break;
				}

				prev_origin = &node->record->vec_origin;
				node = prev;
				continue;
			}

			if (delta > (max_time /*+ snapshot_interval*/))
				break;

			if (!prev_origin)
				prev_origin = &node->record->vec_origin;
		}

		if (!can_restore_to_simulation_time(node->record->simulation_time))
		{
			if (should_lag_fix != nullptr)
				*should_lag_fix = out_records->size() == 0;

			break;
		}

		#if 0
		if (is_delta_too_big(*prev_origin, node->record->origin))
		{
			if (out_records->empty() && first_record_valid)
				out_records->push_back(list.back().record);

			if (should_lag_fix != nullptr)
				*should_lag_fix = !first_record_valid;

			break;
		}
		#endif

		out_records->push_back(node->record);

		prev_origin = &node->record->vec_origin;
		node = prev;
	}
}

void history::update()
{
	for (size_t i = 1; i <= interfaces::entity_list->get_highest_entity_index(); i++)
	{
		if (i == interfaces::engine->get_local_player())
			continue;

		c_base_entity* entity = interfaces::entity_list->get_entity(i);

		if (!entity || !entity->is_player() || !entity->is_alive())
		{
			for (auto& node : snapshots[i])
			{
				delete node->record;
				delete node;
			}

			snapshots[i].clear();

			continue;
		}

		snapshot* new_record = new snapshot;
		node* new_node = new node;

		new_record->arrive_time = utilities::ticks_to_time(estimate_server_arrive_tick());
		new_record->simulation_time = entity->get_simulation_time();
		new_record->vec_origin = entity->get_abs_origin();

		entity->invalidate_bone_cache();
		entity->get_client_renderable()->setup_bones(new_record->bone_to_world, MAX_STUDIO_BONES, BONE_USED_BY_ANYTHING, interfaces::global_vars->curtime);

		new_node->record = new_record;

		if (!snapshots[i].empty())
			new_node->prev = snapshots[i].back();

		snapshots[i].push_back(new_node);
	}
}
