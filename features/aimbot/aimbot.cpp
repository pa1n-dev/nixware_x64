#include "aimbot.h"
#include "penetrate_walls.h"

void aimbot::run(c_user_cmd* cmd)
{
	if (!settings::aimbot::globals::enable)
		return;

	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (!local_player || !local_player->is_alive())
		return;

	c_base_combat_weapon* weapon = local_player->get_active_weapon();
	if (!weapon)
		return;

	target_info_t target_info = find_best_target(cmd, local_player, weapon);
	if (!target_info.entity)
		return;

	if (!settings::aimbot::globals::hotkey.check())
		return;

	cmd->view_angles = target_info.shoot_angle;

	if (!settings::aimbot::globals::silent)
		interfaces::engine->set_view_angles(cmd->view_angles);

	if (settings::aimbot::globals::automatic_fire)
		cmd->buttons |= IN_ATTACK;
}

target_info_t aimbot::find_best_target(c_user_cmd* cmd, c_base_entity* local_player, c_base_combat_weapon* weapon)
{
	target_info_t target_info;

	c_vector eye_position = local_player->get_eye_position();

	for (size_t i = 0; i <= interfaces::entity_list->get_highest_entity_index(); i++)
	{
		c_base_entity* entity = interfaces::entity_list->get_entity(i);

		if (!entity)
			continue;

		if (!entity->is_player())
			continue;

		if (!entity->is_alive())
			continue;

		if (entity->is_dormant())
			continue;

		if (entity == local_player)
			continue;

		c_vector shoot_pos;
		if (!get_hit_position(local_player, entity, shoot_pos))
			continue;

		q_angle shoot_angle = utilities::calc_angle(eye_position, shoot_pos);

		float fov = utilities::get_fov(cmd->view_angles, shoot_angle);

		if (fov > settings::aimbot::globals::fov)
			continue;

		if (fov > target_info.fov)
			continue;

		target_info.fov = fov;		
		target_info.entity = entity;
		target_info.shoot_pos = shoot_pos;
		target_info.shoot_angle = shoot_angle;
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

	studiohdr_t* studiohdr = interfaces::model_info->get_studio_model(model);
	if (!studiohdr)
		return false;

	mstudiohitboxset_t* studiohitboxset = studiohdr->hitbox_set(0);
	if (!studiohitboxset)
		return false;

	for (int i = 0; i < studiohitboxset->num_hitboxes; i++)
	{
		mstudiobbox_t* hitbox = studiohitboxset->hitbox(i);
		if (!hitbox)
			continue;

		c_vector mins, maxs;
		math::vector_transform(hitbox->bb_min, matrix[hitbox->bone], mins);
		math::vector_transform(hitbox->bb_max, matrix[hitbox->bone], maxs);
		shoot_pos = (mins + maxs) * 0.5;

		if (penetrate_walls::is_visible(local_player, entity, shoot_pos))
			return true;
	}

	c_vector pos = entity->get_render_origin();
	c_vector mins = pos + entity->get_collidable()->mins();
	c_vector maxs = pos + entity->get_collidable()->maxs();
	shoot_pos = (mins + maxs) * 0.5;

	if (penetrate_walls::is_visible(local_player, entity, shoot_pos))
		return true;

	return false;
}