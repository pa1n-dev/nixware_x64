#pragma once
#include <windows.h>

#include "../dependencies/xorstr/xorstr.h"
#include "../sdk/interfaces.h"

struct box_t
{
    float left, top, right, bottom;
};

namespace utilities
{
	bool game_is_full_loaded();
	bool get_entity_box(c_base_entity* entity, box_t& box);
}