#pragma once
#include <windows.h>

#include "../dependencies/xorstr/xorstr.h"
#include "../sdk/interfaces.h"
#include "../settings.h"

struct box_t
{
    float left, top, right, bottom;
};

namespace utilities
{
	bool game_is_full_loaded();
	bool screen_transform(const c_vector& in, c_vector& out);
	bool world_to_screen(const c_vector& in, c_vector& out);
	bool get_entity_box(c_base_entity* entity, box_t& box);
}