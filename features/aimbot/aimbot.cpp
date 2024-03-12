 #include "aimbot.h"
#include "penetrate_walls.h"
#include "backtrack/history.h"
#include "backtrack/lag_compensation.h"

void aimbot::run(c_user_cmd* cmd)
{
	target_info = {};

	if (!settings::aimbot::globals::enable)
		return;

	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (!local_player || !local_player->is_alive())
		return;

	c_base_combat_weapon* weapon = local_player->get_active_weapon();
	if (!weapon)
		return;

	target_info = find_best_target(cmd, local_player);
	if (!target_info.entity)
		return;

	if (settings::menu::opened)
		return;

	if (cmd->is_typing || cmd->is_world_clicking)
		return;

	if (weapon->is_holding_tool() || !weapon->can_shoot())
		return;

	if (!settings::aimbot::globals::hotkey.check())
		return;

	if (lag_compensation::get_is_locked())
		return;

	smooth(cmd->view_angles, target_info.shoot_angle);

	cmd->view_angles = target_info.shoot_angle;

	if (!settings::aimbot::globals::silent)
		interfaces::engine->set_view_angles(cmd->view_angles);

	if (settings::aimbot::globals::automatic_fire)
		cmd->buttons |= IN_ATTACK;

	bool adjust_interp;
	history::can_restore_to_simulation_time(target_info.simulation_time, &adjust_interp);

	if (adjust_interp)
	{
		float interp = utilities::ticks_to_time(interfaces::global_vars->tick_count) - target_info.simulation_time;
		lag_compensation::update_desired_values(true, interp, 1.f);
	}
	else
	{
		//cmd->tick_count = utilities::time_to_ticks(target_info.simulation_time);
		//lag_compensation::update_desired_values(false, 0.f, 0.f);
	}
}

aimbot::target_info_t aimbot::find_best_target(c_user_cmd* cmd, c_base_entity* local_player)
{
	target_info_t target_info;
	priority_info_t& priority_info = target_info.priority_info;

	const c_vector& eye_position = local_player->get_eye_position();
	const c_vector& origin = local_player->get_abs_origin();
	const q_angle& view_angles = cmd->view_angles;

	for (size_t i = 1; i <= interfaces::entity_list->get_highest_entity_index(); i++)
	{
		c_base_entity* entity = interfaces::entity_list->get_entity(i);

		if (!entity || !entity->is_player() || !entity->is_alive() || entity->is_dormant() || entity == local_player)
			continue;

		float simulation_time = entity->get_simulation_time();

		c_vector shoot_pos;

		if (!get_hit_position(local_player, entity, shoot_pos))
		{
			if (!settings::aimbot::accuracy::backtrack)
				continue;

			std::vector<lag_record> records;
			history::get_usable_records(i, &records, settings::aimbot::accuracy::backtrack);

			if (records.empty())
				continue;

			auto record = records.back();

			if (!get_hit_position(local_player, entity, shoot_pos, record.bone_to_world))
				continue;

			simulation_time = record.simulation_time;
		}

		q_angle shoot_angle = utilities::calc_angle(eye_position, shoot_pos);

		float fov = utilities::get_fov(view_angles, shoot_angle);

		if (fov > settings::aimbot::globals::fov)
			continue;
		
		int distance = entity->get_abs_origin().distance_to(origin);
		int health = entity->get_health();

        bool should_skip = false;
        switch (settings::aimbot::globals::priority) 
		{
            case 0: should_skip = fov > priority_info.fov; break;
            case 1: should_skip = distance > priority_info.distance; break;
            case 2: should_skip = health > priority_info.health; break;
        }

        if (should_skip)
            continue;

		priority_info.fov = fov;
		priority_info.distance = distance;
		priority_info.health = health;

		target_info.entity = entity;
		target_info.shoot_pos = shoot_pos;
		target_info.shoot_angle = shoot_angle;
		target_info.simulation_time = simulation_time;
	}

	return target_info;
}

bool aimbot::check_hitbox_group(int group) 
{
	switch (settings::aimbot::globals::hitbox) 
	{
	case 0: return group == HITGROUP_HEAD;
	case 1: return group == HITGROUP_CHEST;
	case 2: return group == HITGROUP_STOMACH;
	default: return true;
	}
}

bool aimbot::get_hit_position(c_base_entity* local_player, c_base_entity* entity, c_vector& shoot_pos, matrix3x4* bone_to_world)
{
	if (bone_to_world == nullptr)
	{
		bone_to_world = new matrix3x4[MAX_STUDIO_BONES];

		entity->invalidate_bone_cache();
		if (!entity->get_client_renderable()->setup_bones(bone_to_world, MAX_STUDIO_BONES, BONE_USED_BY_ANYTHING, interfaces::global_vars->curtime))
			return false;
	}

	void* model = entity->get_client_renderable()->get_model();
	if (!model)
		return false;

	studiohdr_t* hdr = interfaces::model_info->get_studio_model(model);
	if (!hdr)
		return false;

	mstudiohitboxset_t* hitbox_set = hdr->hitbox_set(0);
	if (!hitbox_set)
		return false;

	bool found_hitbox = false;

	for (int i = 0; i < hitbox_set->num_hitboxes; i++)
	{
		mstudiobbox_t* hitbox = hitbox_set->hitbox(i);
		if (!hitbox)
			continue;

		if (!check_hitbox_group(hitbox->group))
			continue;

		c_vector mins, maxs;
		math::vector_transform(hitbox->bb_min, bone_to_world[hitbox->bone], mins);
		math::vector_transform(hitbox->bb_max, bone_to_world[hitbox->bone], maxs);
		shoot_pos = (mins + maxs) * 0.5;

		if (penetrate_walls::is_visible(local_player, entity, shoot_pos))
			return true;

		found_hitbox = true;
	}
	
	if (!found_hitbox)
	{
		const c_vector& pos = entity->get_abs_origin();
		const c_vector& mins = pos + entity->get_collidable()->mins();
		const c_vector& maxs = pos + entity->get_collidable()->maxs();
		shoot_pos = (mins + maxs) * 0.5;

		return penetrate_walls::is_visible(local_player, entity, shoot_pos);
	}

	return false;
}

void aimbot::smooth(const q_angle& view_angles, q_angle& angle)
{
	if (!settings::aimbot::accuracy::smooth)
		return;

	angle.normalize();
	angle.clamp();

	q_angle delta = angle - view_angles;
	delta.normalize();
	delta.clamp();

	angle = view_angles + delta / settings::aimbot::accuracy::smooth;
}