#include "aimbot.h"
#include "penetrate_walls.h"

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

	cmd->view_angles = target_info.shoot_angle;

	if (!settings::aimbot::globals::silent)
		interfaces::engine->set_view_angles(cmd->view_angles);

	if (settings::aimbot::globals::automatic_fire)
		cmd->buttons |= IN_ATTACK;
}

target_info_t aimbot::find_best_target(c_user_cmd* cmd, c_base_entity* local_player)
{
	target_info_t target_info;
	priority_info_t& priority_info = target_info.priority_info;

	c_vector eye_position = local_player->get_eye_position();
	c_vector render_origin = local_player->get_render_origin();

	for (size_t i = 1; i <= interfaces::entity_list->get_highest_entity_index(); i++)
	{
		c_base_entity* entity = interfaces::entity_list->get_entity(i);

		if (!entity || !entity->is_player() || !entity->is_alive() || entity->is_dormant() || entity == local_player)
			continue;

		c_vector shoot_pos;
		if (!get_hit_position(local_player, entity, shoot_pos))
			continue;

		q_angle shoot_angle = utilities::calc_angle(eye_position, shoot_pos);

		float fov = utilities::get_fov(cmd->view_angles, shoot_angle);
		std::cout << fov << std::endl;
		if (fov > settings::aimbot::globals::fov)
			continue;
		
		int distance = entity->get_render_origin().distance_to(render_origin);
		int health = entity->get_health();

		switch (settings::aimbot::globals::priority)
		{
		case 0:
			if (fov > priority_info.fov)
				continue;

			priority_info.fov = fov;
			break;
		case 1:
			if (distance > priority_info.distance)
				continue;

			priority_info.distance = distance;
			break;
		case 2:
			if (health > priority_info.health)
				continue;

			priority_info.health = health;
			break;
		}

		target_info.entity = entity;
		target_info.shoot_pos = shoot_pos;
		target_info.shoot_angle = shoot_angle;

		priority_info.fov = fov;
		priority_info.distance = distance;
		priority_info.health = health;
	}

	return target_info;
}

bool aimbot::get_hit_position(c_base_entity* local_player, c_base_entity* entity, c_vector& shoot_pos)
{
	matrix3x4_t matrix[MAX_STUDIO_BONES];

	if (!entity->get_client_renderable()->setup_bones(matrix, MAX_STUDIO_BONES, BONE_USED_BY_HITBOX, interfaces::global_vars->curtime))
		return false;

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

		if ((settings::aimbot::globals::hitbox == 0 && hitbox->group != HITGROUP_HEAD) || (settings::aimbot::globals::hitbox == 1 && hitbox->group != HITGROUP_CHEST) || (settings::aimbot::globals::hitbox == 2 && hitbox->group != HITGROUP_STOMACH))
			continue;

		c_vector mins, maxs;
		math::vector_transform(hitbox->bb_min, matrix[hitbox->bone], mins);
		math::vector_transform(hitbox->bb_max, matrix[hitbox->bone], maxs);
		shoot_pos = (mins + maxs) * 0.5;

		if (penetrate_walls::is_visible(local_player, entity, shoot_pos))
			return true;

		found_hitbox = true;
	}
	
	if (found_hitbox)
	{
		c_vector pos = entity->get_render_origin();
		c_vector mins = pos + entity->get_collidable()->mins();
		c_vector maxs = pos + entity->get_collidable()->maxs();
		shoot_pos = (mins + maxs) * 0.5;

		if (penetrate_walls::is_visible(local_player, entity, shoot_pos))
			return true;
	}

	return false;
}