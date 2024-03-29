#pragma once
#include "../../hooks/hooks.h"

namespace animfix
{
	inline c_hl2mp_player_anim_state* real_anim_state;
	inline multi_player_movement_data_t* real_move_data;

	inline matrix3x4 real_matrix[MAX_STUDIO_BONES];
	inline matrix3x4 fake_matrix[MAX_STUDIO_BONES];

	inline bool created_real_matrix = false;
	inline bool created_fake_matrix = false;

	inline bool allow_anim_state_update = false;
	inline bool allow_anim_state_reset = true;

	inline int ticks_elapsed = 0;

	bool reset();
	void update_real_anim_state(c_user_cmd* cmd);
	void update_fake_anim_state(c_user_cmd* cmd, c_base_entity* local_player);
	void update_real_bones(c_base_entity* local_player);
	void update_fake_bones(c_base_entity* local_player);
	void swap_anim_states(c_base_entity* local_player);
	void run(c_user_cmd* cmd, bool send_packet);
}