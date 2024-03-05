#pragma once
#include "../../../hooks/hooks.h"

namespace lag_compensation
{
    inline float interp;
    inline float ratio;
    inline bool interpolate;
    inline bool has_to_change;
    inline bool has_to_reset;
    inline int reset_ticks;

    void write_user_cmd_delta_to_buffer_callback();
    void reset_values();
    void update_desired_values(bool _interpolate, float _interp = -1.f, float _ratio = -1.f);
    void cancel_updates();
    bool get_is_locked();
}