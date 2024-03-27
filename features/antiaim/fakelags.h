#pragma once
#include "../../hooks/hooks.h"

namespace fakelags
{
	bool run(c_user_cmd* cmd);
	void apply(bool send_packet);
}