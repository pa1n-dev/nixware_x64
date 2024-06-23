#pragma once
#include "../../hooks/hooks.h"

namespace obs_bypass
{
	void frame_stage_notify(ñlient_frame_stage_t stage);
	void render_view(i_view_render* view_render, c_view_setup& view, int flags, int to_draw);

	inline i_texture* render_texture = nullptr;
	inline bool in_streamproof_view = false;
}