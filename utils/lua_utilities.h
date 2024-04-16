#pragma once

#include "../dependencies/xorstr/xorstr.h"
#include "../sdk/interfaces.h"

namespace lua_utilities
{
	const char* get_name(c_base_entity* entity);
	const char* get_rank_table_name(c_base_entity* entity);
	const char* get_user_group(c_base_entity* entity);
	const char* get_rp_jobs_list(int team);
	int get_job_without_disguise(c_base_entity* entity);
	const char* get_team_name(c_base_entity* entity);
	const char* get_weapon_print_name(c_base_combat_weapon* weapon);
	const char* get_weapon_base(c_base_combat_weapon* weapon);
	float get_m9k_spread(c_user_cmd* cmd, c_base_combat_weapon* weapon);
	float get_ptp_spread(c_base_combat_weapon* weapon);
	float get_weapon_max_spread_inc(c_base_combat_weapon* weapon);
	float get_weapon_cur_cone(c_base_combat_weapon* weapon);
	const char* language_get_phrase(const char* phrase);
	void random_seed(float seed);
	float rand(float min, float max);
}