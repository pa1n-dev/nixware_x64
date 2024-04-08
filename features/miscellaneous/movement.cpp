#include "movement.h"

void movement::run(c_user_cmd* cmd)
{
    c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
    if (!local_player || !local_player->is_alive())
        return;

    if (local_player->get_move_type() == MOVETYPE_NOCLIP || local_player->get_move_type() == MOVETYPE_LADDER || local_player->get_flags() & FL_INWATER)
        return;

    if (settings::miscellaneous::movement::bhop)
    {
        if (cmd->buttons & IN_JUMP && !(local_player->get_flags() & FL_ONGROUND))
            cmd->buttons &= ~IN_JUMP;
    }

	//https://github.com/CSGOLeaks/Legendware-V3/blob/de63ad96fe233f81c5952c327469239de223f08c/cheats/misc/airstrafe.cpp#L40
	if (settings::miscellaneous::movement::air_strafe)
	{
        static auto old_view_yaw = 0.0f;

        static auto cl_sidespeed = interfaces::cvar->find_var(xorstr("cl_sidespeed"));
        if (!cl_sidespeed)
            return;

        if (local_player->get_flags() & FL_ONGROUND || local_player->get_move_type() != MOVETYPE_WALK)
            return;

        float forward_move = cmd->forward_move;
        float side_move = cmd->side_move;

        if (!forward_move && !side_move)
            return;

        c_vector velocity = local_player->get_velocity();
        velocity.z = 0.f;

        if (velocity.length_2d() < 15.f)
            return;

        cmd->forward_move = 0.f;
        cmd->side_move = 0.f;

        float turn_direction_modifier = cmd->command_number % 2 == 0 ? 1.f : -1.f;
        float side_speed = cl_sidespeed->get_float();
        float turn_angle = atan2(-side_move, forward_move);

        float view_yaw = cmd->view_angles.y + turn_angle * math::RAD_PI_F;
 
        float strafe_angle = std::clamp(math::rad2deg(atan(15.f / velocity.length_2d())), 0.f, 90.f);
        float yaw_delta = math::normalize_yaw(view_yaw - old_view_yaw);
        old_view_yaw = view_yaw;

        float abs_yaw_delta = fabs(yaw_delta);

        if (abs_yaw_delta <= strafe_angle || abs_yaw_delta >= 30.f)
        {
            c_vector velocity_angles;
            math::vector_to_angle(velocity, velocity_angles);

            float velocity_angle_yaw_delta = math::normalize_yaw(view_yaw - velocity_angles.y);
            float velocity_degree = std::clamp(math::rad2deg(atan(10.f / velocity.length_2d())), 0.f, 90.f) * 0.01f;

            if (velocity_angle_yaw_delta <= velocity_degree || velocity.length_2d() <= 15.f)
            {
                if (-velocity_degree <= velocity_angle_yaw_delta || velocity.length_2d() <= 15.f)
                {
                    view_yaw += strafe_angle * turn_direction_modifier;
                    cmd->side_move = side_speed * turn_direction_modifier;
                }
                else
                {
                    view_yaw = velocity_angles.y - velocity_degree;
                    cmd->side_move = side_speed;
                }
            }
            else
            {
                view_yaw = velocity_angles.y + velocity_degree;
                cmd->side_move = -side_speed;
            }
        }
        else if (yaw_delta > 0.f)
            cmd->side_move = -side_speed;
        else if (yaw_delta < 0.f)
            cmd->side_move = side_speed;

		c_vector move = c_vector(cmd->forward_move, cmd->side_move, 0.f);
		float speed = move.length();

		c_vector move_angles;
		math::vector_to_angle(move, move_angles);

		float normalized_x = fmod(cmd->view_angles.x + 180.f, 360.f) - 180.f;
		float normalized_y = fmod(cmd->view_angles.y + 180.f, 360.f) - 180.f;

		float yaw = math::deg2rad(normalized_y - view_yaw + move_angles.y);

		if (normalized_x >= 90.f || normalized_x <= -90.f || 
            cmd->view_angles.x >= 90.f && cmd->view_angles.x <= 200.f || 
            cmd->view_angles.x <= -90.f && cmd->view_angles.x <= 200.f)
			cmd->forward_move = -cos(yaw) * speed;
		else
			cmd->forward_move = cos(yaw) * speed;

		cmd->side_move = sin(yaw) * speed;
	}
}

void movement::fix(c_user_cmd* cmd, c_user_cmd old_cmd)
{
	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (!local_player || !local_player->is_alive())
		return;

	if (local_player->get_move_type() == MOVETYPE_NOCLIP || local_player->get_move_type() == MOVETYPE_LADDER || local_player->get_flags() & FL_INWATER)
		return;

    float delta_yaw = math::deg2rad(cmd->view_angles.y - old_cmd.view_angles.y);

	cmd->forward_move = (cos(delta_yaw) * old_cmd.forward_move) - (sin(delta_yaw) * old_cmd.side_move);
	cmd->side_move = (sin(delta_yaw) * old_cmd.forward_move) + (cos(delta_yaw) * old_cmd.side_move);
}