#include "penetrate_walls.h"

bool penetrate_walls::is_visible(c_base_entity* local_player, c_base_entity* entity, c_vector end)
{
    c_vector eye_position = local_player->get_eye_position();

    trace_t trace;
    c_trace_filter filter;
    filter.skip = local_player;

    ray_t ray(eye_position, end);

    interfaces::engine_trace->trace_ray(ray, MASK_SHOT, &filter, &trace);

    return (trace.entity == entity || trace.fraction >= 0.98f);
}