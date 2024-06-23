#include "animfix.h"

bool animfix::can_update_animstates(c_base_entity* local_player)
{
	static c_hl2mp_player_anim_state* prev_anim_state = local_player->get_anim_state();
	if (local_player->get_anim_state() != prev_anim_state)
	{
		if (real_anim_state)
		{
			real_anim_state->destructor();
			real_anim_state = nullptr;
		}

		if (real_move_data)
		{
			delete real_move_data;
			real_move_data = nullptr;
		}

		prev_anim_state = local_player->get_anim_state();

		need_anim_state_reset = true;
	}

	if (!local_player || !local_player->is_alive() || local_player->is_dormant())
	{
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
	{
		c_vector origin = local_player->get_abs_origin();

		for (auto& i : real_matrix)
		{
			i[0][3] -= origin.x;
			i[1][3] -= origin.y;
			i[2][3] -= origin.z;
		}

		created_real_matrix = true;
	}
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
	if (!can_update_animstates(local_player))
		return;

	if (need_anim_state_reset)
	{
		if (!real_anim_state)
			real_anim_state = local_player->create_anim_state();

		if (!real_move_data)
			real_move_data = new multi_player_movement_data_t{};

		real_anim_state->init(local_player, *real_move_data);

		need_anim_state_reset = false;
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