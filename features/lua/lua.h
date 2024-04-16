#pragma once
#include "../../hooks/hooks.h"

namespace lua
{
	void run_string(const std::string& path);
	void dumper(const std::string& filename, const std::string& string_to_run);
}