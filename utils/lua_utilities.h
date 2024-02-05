#pragma once

#include "../dependencies/xorstr/xorstr.h"
#include "../sdk/interfaces.h"

namespace lua_utilities
{
	const char* language_get_phrase(const char* phrase);
	const char* get_weapon_base(c_base_combat_weapon* weapon);
	float get_weapon_spread(c_base_combat_weapon* weapon);
}