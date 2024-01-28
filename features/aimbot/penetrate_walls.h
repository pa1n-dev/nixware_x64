#pragma once
#include "../../hooks/hooks.h"

namespace penetrate_walls
{
    bool is_visible(c_base_entity* local_player, c_base_entity* entity, c_vector end);
}