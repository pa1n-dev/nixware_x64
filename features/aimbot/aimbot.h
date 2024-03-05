#pragma once
#include "../../hooks/hooks.h"

namespace aimbot
{
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
		float simulation_time = 0.f;
		priority_info_t priority_info;
	};

	inline target_info_t target_info;

	void run(c_user_cmd* cmd);
	target_info_t find_best_target(c_user_cmd* cmd, c_base_entity* local_player);
	bool check_hitbox_group(int group);
	bool get_hit_position(c_base_entity* local_player, c_base_entity* entity, c_vector& shoot_pos, matrix3x4* bone_to_world = nullptr);
	void smooth(const q_angle& view_angles, q_angle& angle);
}