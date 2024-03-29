#pragma once
#include "../../hooks/hooks.h"

struct priority_info
{
	float fov = FLT_MAX;
	float distance = FLT_MAX;
	float health = FLT_MAX;
};

struct target_info
{
	c_base_entity*	entity = nullptr;
	c_vector		shoot_pos;
	q_angle			shoot_angle;
	float			simulation_time;
	priority_info	priority_info;
};

namespace aimbot
{
	inline target_info target;

	void run(c_user_cmd* cmd);
	target_info find_best_target(c_user_cmd* cmd, c_base_entity* local_player);
	bool check_hitbox_group(int group);
	bool get_hit_position(c_base_entity* local_player, c_base_entity* entity, c_vector& shoot_pos, std::shared_ptr<matrix3x4[]> bone_to_world = nullptr);
	void smooth(c_user_cmd* cmd, q_angle& angle);
}