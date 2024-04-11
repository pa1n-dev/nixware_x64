#pragma once
#include "../../hooks/hooks.h"

namespace miscellaneous
{
	void run();
	void third_person(c_view_setup& view);
	void lua_dumper(std::string filename, std::string string_to_run);
}