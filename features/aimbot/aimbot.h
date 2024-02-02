#pragma once
#include "../../hooks/hooks.h"

struct priority_info_t
{
	float fov = FLT_MAX;
	float distance = FLT_MAX;
	float health = FLT_MAX;
};

struct target_info_t
{
	c_base_entity* entity = nullptr;

	c_vector shoot_pos;
	q_angle shoot_angle;

	priority_info_t priority_info;
};

namespace aimbot
{
	inline target_info_t target_info;

	void run(c_user_cmd* cmd);
	target_info_t find_best_target(c_user_cmd* cmd, c_base_entity* local_player);
	bool get_hit_position(c_base_entity* local_player, c_base_entity* entity, c_vector& shoot_pos);
	void smooth(c_user_cmd* cmd, q_angle& angle);
}