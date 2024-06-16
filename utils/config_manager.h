#pragma once
#include "../sdk/interfaces.h"

namespace config_manager
{
	void load(std::string name);
	void save(std::string name);
}