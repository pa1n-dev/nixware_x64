#pragma once
#include "../../hooks/hooks.h"

namespace movement
{
	void run(c_user_cmd* cmd);
	void air_strafe(c_user_cmd* cmd, c_base_entity* local_player);
	void fix(c_user_cmd* cmd, c_user_cmd old_cmd);
}