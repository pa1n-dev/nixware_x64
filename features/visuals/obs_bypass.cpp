#include "obs_bypass.h"

void obs_bypass::frame_stage_notify(ñlient_frame_stage_t stage)
{
    if (stage != frame_render_start)
        return;

    if (render_texture)
        return;

    interfaces::material_system->begin_render_target_allocation();
    render_texture = interfaces::material_system->create_named_render_target_texture_ex(xorstr("_rt_obs_bypass_texture"), 1, 1, rt_size_full_frame_buffer, interfaces::material_system->get_back_buffer_format(), material_rt_depth_shared, textureflags_clamps | textureflags_clamps, 0);
    interfaces::material_system->end_render_target_allocation();
}

void obs_bypass::render_view(i_view_render* view_render, c_view_setup& view, int flags, int to_draw)
{
    if (!render_texture)
        return;

    if (!interfaces::engine->is_in_game())
        return;

    c_mat_render_context* render_context = interfaces::material_system->get_render_context();
    if (!render_context)
        return;

    render_context->copy_render_target_to_texture(render_texture);
    render_context->begin_render();
    render_context->set_render_target(nullptr);

    in_streamproof_view = true;
    hooks::handles::originals::render_view(view_render, view, flags, to_draw);
    in_streamproof_view = false;

    render_context->end_render();
    render_context->set_render_target(render_texture);
}