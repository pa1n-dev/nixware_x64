#pragma once
#include "../../../hooks/hooks.h"

namespace history
{
	struct snapshot
	{
		float arrive_time = 0.0f;
		float simulation_time = 0.0f;

		c_vector vec_origin;

		matrix3x4* bone_to_world = new matrix3x4[MAX_STUDIO_BONES];
	};

	struct node
	{
		snapshot* record = nullptr;
		node* prev = nullptr;
	};

	static std::map<int, std::vector<node*>> snapshots;

	//float get_lerp_time();
	//float get_lowest_possible_lerp_time(int* update_rate = nullptr);
	int estimate_server_arrive_tick();
	bool can_restore_to_simulation_time(float simulation_time, bool* need_to_adjust_interp = nullptr);
	bool is_delta_too_big(const c_vector& from, const c_vector& to);
	void get_usable_records_for_entity(c_base_entity* entity, std::vector<snapshot*>* out_records, float min_time = -1.f, float max_time = -1.f, bool* should_lag_fix = nullptr);
	void get_usable_records_for_index(int index, std::vector<snapshot*>* out_records, float min_time = -1.f, float max_time = -1.f, bool* should_lag_fix = nullptr);
	void update();
}