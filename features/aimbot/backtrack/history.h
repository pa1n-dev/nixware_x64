#pragma once
#include "../../../hooks/hooks.h"

struct lag_record
{
	std::shared_ptr<matrix3x4[]> bone_to_world;

	float arrive_time;
	float simulation_time;
	c_vector origin;
};

namespace history
{
	static std::unordered_map<int, std::vector<lag_record>> records;

	float get_lerp_time();
	int estimate_server_arrive_tick();
	bool is_delta_too_big(const c_vector& from, const c_vector& to);
	bool can_restore_to_simulation_time(float simulation_time, bool* need_to_adjust_interp = nullptr);
	bool get_latest_record(int index, lag_record& out_record);
	void update();
}