#include "movement.h"

void movement::fix_movement(c_user_cmd* cmd, c_user_cmd old_cmd)
{
	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (local_player->get_move_type() == MOVETYPE_NOCLIP || local_player->get_move_type() == MOVETYPE_LADDER || local_player->get_flags() & FL_INWATER)
		return;

	float f1, f2, yaw_delta = cmd->view_angles.y - old_cmd.view_angles.y;

	if (old_cmd.view_angles.y < 0.f)
		f1 = 360.0f + old_cmd.view_angles.y;
	else
		f1 = old_cmd.view_angles.y;

	if (cmd->view_angles.y < 0.0f)
		f2 = 360.0f + cmd->view_angles.y;
	else
		f2 = cmd->view_angles.y;

	if (f2 < f1)
		yaw_delta = abs(f2 - f1);
	else
		yaw_delta = 360.0f - abs(f1 - f2);

	yaw_delta = 360.0f - yaw_delta;

	cmd->forward_move = cos(math::deg2rad(yaw_delta)) * old_cmd.forward_move + cos(math::deg2rad(yaw_delta + 90.f)) * old_cmd.side_move;
	cmd->side_move = sin(math::deg2rad(yaw_delta)) * old_cmd.forward_move + sin(math::deg2rad(yaw_delta + 90.f)) * old_cmd.side_move;
}