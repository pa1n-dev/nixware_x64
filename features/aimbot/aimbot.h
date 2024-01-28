#pragma once
#include "../../hooks/hooks.h"

struct target_info_t
{
	c_base_entity* entity = nullptr;

	c_vector shoot_pos;
	q_angle shoot_angle;

	float fov = FLT_MAX;
};

namespace aimbot
{
	void run(c_user_cmd* cmd);
	target_info_t find_best_target(c_user_cmd* cmd, c_base_entity* local_player, c_base_combat_weapon* weapon);
	bool get_hit_position(c_base_entity* local_player, c_base_entity* entity, c_vector& shoot_pos);
}