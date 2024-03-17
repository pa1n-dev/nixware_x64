#pragma once
#include "../../../hooks/hooks.h"

struct lag_record
{
	float arrive_time = 0.0f;
	float simulation_time = 0.0f;

	c_vector vec_origin;
	c_vector vec_mins;
	c_vector vec_maxs;
	q_angle ang_render;

	int sequence;
	float cycle;
	float eye_yaw;
	float eye_pitch;

	matrix3x4 bone_to_world[MAX_STUDIO_BONES];
};

namespace history
{
	static std::unordered_map<int, std::vector<lag_record>> records;

	float get_lerp_time();
	int estimate_server_arrive_tick();
	bool is_delta_too_big(const c_vector& from, const c_vector& to);
	bool can_restore_to_simulation_time(float simulation_time, bool* need_to_adjust_interp = nullptr);
	void get_usable_records(int index, std::vector<lag_record>* out_records, float max_time = -1.f);
	void update();
}