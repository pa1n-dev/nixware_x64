#pragma once
#include "../../hooks/hooks.h"

namespace predict_spread
{
	void run(c_user_cmd* cmd);
	void engine_spread(c_user_cmd* cmd, float spread);
	void cone_spread(c_user_cmd* cmd, float cone, float seed);
}