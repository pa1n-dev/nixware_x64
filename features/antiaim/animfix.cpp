#include "animfix.h"

bool animfix::reset()
{
	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (!local_player || !local_player->is_alive() || local_player->is_dormant())
	{
		if (!local_player)
		{
			if (real_anim_state)
			{
				real_anim_state->~c_hl2mp_player_anim_state();
				real_anim_state = nullptr;
			}
		}
		else
			allow_anim_state_reset = true;

		if (real_move_data)
		{
			delete real_move_data;
			real_move_data = nullptr;
		}

		created_real_matrix = false;
		created_fake_matrix = false;

		return false;
	}

	return true;
}

void animfix::update_real_anim_state(c_user_cmd* cmd)
{
	allow_anim_state_update = true;

	real_anim_state->update(
		cmd->view_angles.y,
		cmd->view_angles.x
	);
}

void animfix::update_fake_anim_state(c_user_cmd* cmd, c_base_entity* local_player)
{
	allow_anim_state_update = true;

	local_player->get_anim_state()->update(
		cmd->view_angles.y,
		cmd->view_angles.x
	);
}

void animfix::update_real_bones(c_base_entity* local_player)
{
	local_player->invalidate_bone_cache();
	if (local_player->get_client_renderable()->setup_bones(real_matrix, MAX_STUDIO_BONES, BONE_USED_BY_ANYTHING, interfaces::global_vars->curtime))
		created_real_matrix = true;
}

void animfix::update_fake_bones(c_base_entity* local_player)
{
	local_player->invalidate_bone_cache();
	if (local_player->get_client_renderable()->setup_bones(fake_matrix, MAX_STUDIO_BONES, BONE_USED_BY_ANYTHING, interfaces::global_vars->curtime))
		created_fake_matrix = true;
}

void animfix::swap_anim_states(c_base_entity* local_player)
{
	std::swap(*real_anim_state, *local_player->get_anim_state());
}

void animfix::run(c_user_cmd* cmd, bool send_packet)
{
	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (!local_player || !local_player->is_alive())
		return;

	bool create_real = !real_anim_state;
	bool init_real = allow_anim_state_reset || create_real;

	if (create_real)
		real_anim_state = local_player->create_anim_state();

	if (init_real) 
	{
		if (!real_move_data)
			real_move_data = new multi_player_movement_data_t{};

		real_anim_state->init(local_player, *real_move_data);

		allow_anim_state_reset = false;
	}

	float ft = interfaces::global_vars->frametime;
	interfaces::global_vars->frametime = interfaces::global_vars->interval_per_tick;

	q_angle old = local_player->eye_angles();
	local_player->eye_angles() = cmd->view_angles;

	update_real_anim_state(cmd);

	if (send_packet)
	{
		swap_anim_states(local_player);
		update_real_bones(local_player);
		swap_anim_states(local_player);

		interfaces::global_vars->frametime = interfaces::global_vars->interval_per_tick * ticks_elapsed;

		update_fake_anim_state(cmd, local_player);
		update_fake_bones(local_player);

		ticks_elapsed = 1;
	}
	else
		ticks_elapsed++;

	local_player->eye_angles() = old;
	interfaces::global_vars->frametime = ft;
}