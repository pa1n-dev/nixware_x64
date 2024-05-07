#pragma once
#include "../../hooks/hooks.h"

namespace lua
{
	void executor();
	void dumper(const std::string& filename, const std::string& string_to_run);
}