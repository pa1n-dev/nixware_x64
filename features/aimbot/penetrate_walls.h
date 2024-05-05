#pragma once
#include "../../hooks/hooks.h"

namespace penetrate_walls
{
    bool is_visible(c_base_entity* local_player, c_base_entity* entity, c_vector eye_position, c_vector end);
    bool swb(c_base_entity* local_player, c_base_combat_weapon* weapon, c_base_entity* entity, c_vector eye_pos, c_vector shoot_pos);
    bool can_hit(c_base_entity* local_player, c_base_entity* entity, c_vector shoot_pos);
}