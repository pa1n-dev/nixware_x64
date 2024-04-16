#pragma once
#include "../../hooks/hooks.h"

namespace engine_prediction
{
	static unsigned int* prediction_random_seed;

	static float old_curtime;
	static float old_frametime;

	static c_base_entity* player;
	static c_move_data move_data = { };

	void start(c_user_cmd* cmd, c_base_entity* entity = nullptr);
	void end(c_user_cmd* cmd);
}