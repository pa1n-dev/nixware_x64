#pragma once

enum image_format_t
{
    image_format_unknown = -1,
    image_format_rgba8888 = 0,
    image_format_abgr8888,
    image_format_rgb888,
    image_format_bgr888,
    image_format_rgb565,
    image_format_i8,
    image_format_ia88,
    image_format_p8,
    image_format_a8,
    image_format_rgb888_bluescreen,
    image_format_bgr888_bluescreen,
    image_format_argb8888,
    image_format_bgra8888,
    image_format_dxt1,
    image_format_dxt3,
    image_format_dxt5,
    image_format_bgrx8888,
    image_format_bgr565,
    image_format_bgrx5551,
    image_format_bgra4444,
    image_format_dxt1_onebitalpha,
    image_format_bgra5551,
    image_format_uv88,
    image_format_uvwq8888,
    image_format_rgba16161616f,
    image_format_rgba16161616,
    image_format_uvlx8888,
    image_format_r32f,
    image_format_rgb323232f,
    image_format_rgba32323232f,
    image_format_nv_dst16,
    image_format_nv_dst24,
    image_format_nv_intz,
    image_format_nv_rawz,
    image_format_ati_dst16,
    image_format_ati_dst24,
    image_format_nv_null,
    image_format_ati2n,
    image_format_ati1n,
    num_image_formats
};

enum render_target_size_mode_t
{
    rt_size_no_change = 0,
    rt_size_default = 1,
    rt_size_picmip = 2,
    rt_size_hdr = 3,
    rt_size_full_frame_buffer = 4,
    rt_size_offscreen = 5,
    rt_size_full_frame_buffer_rounded_up = 6,
    rt_size_replay_screenshot = 7,
    rt_size_literal = 8
};

enum material_render_target_depth_t
{
    material_rt_depth_shared = 0x0,
    material_rt_depth_separate = 0x1,
    material_rt_depth_none = 0x2,
    material_rt_depth_only = 0x3
};

enum compiled_vtf_flags
{
    textureflags_pointsample = 0x00000001,
    textureflags_trilinear = 0x00000002,
    textureflags_clamps = 0x00000004,
    textureflags_clampt = 0x00000008,
    textureflags_anisotropic = 0x00000010,
    textureflags_hint_dxt5 = 0x00000020,
    textureflags_pwl_corrected = 0x00000040,
    textureflags_normal = 0x00000080,
    textureflags_nomip = 0x00000100,
    textureflags_nolod = 0x00000200,
    textureflags_all_mips = 0x00000400,
    textureflags_procedural = 0x00000800,
    textureflags_onebitalpha = 0x00001000,
    textureflags_eightbitalpha = 0x00002000,
    textureflags_envmap = 0x00004000,
    textureflags_rendertarget = 0x00008000,
    textureflags_depthrendertarget = 0x00010000,
    textureflags_nodebugoverride = 0x00020000,
    textureflags_singlecopy = 0x00040000,
    textureflags_srgb = 0x00080000,
    textureflags_default_pool = 0x00100000,
    textureflags_combined = 0x00200000,
    textureflags_async_download = 0x00400000,
    textureflags_nodepthbuffer = 0x00800000,
    textureflags_skip_initial_download = 0x01000000,
    textureflags_clampu = 0x02000000,
    textureflags_vertextexture = 0x04000000,
    textureflags_ssbump = 0x08000000,
    textureflags_most_mips = 0x10000000,
    textureflags_border = 0x20000000,
    textureflags_unused_40000000 = 0x40000000,
    textureflags_unused_80000000 = 0x80000000
};


class c_mat_render_context
{
public:
    void begin_render()
    {
        return memory::call_v_function<void(__thiscall*)(void*)>(this, 0)(this);
    }

    void end_render()
    {
        return memory::call_v_function<void(__thiscall*)(void*)>(this, 1)(this);
    }

    void set_render_target(i_texture* texture)
    {
        return memory::call_v_function<void(__thiscall*)(void*, i_texture*)>(this, 4)(this, texture);
    }

    i_texture* get_render_target()
    {
        return memory::call_v_function<i_texture*(__thiscall*)(void*)>(this, 5)(this);
    }

    void depth_range(float z_near, float z_far)
    {
        return memory::call_v_function<void(__thiscall*)(void*, float, float)>(this, 9)(this, z_near, z_far);
    }

    void copy_render_target_to_texture(i_texture* texture)
    {
        return memory::call_v_function<void(__thiscall*)(void*, i_texture*)>(this, 15)(this, texture);
    }
};

class c_material_system
{
public:
    image_format_t get_back_buffer_format()
    {
        return memory::call_v_function<image_format_t(__thiscall*)(void*)>(this, 31)(this);
    }

    i_material* create_material(char const* material_name, void* vmt_key_values)
    {
        return memory::call_v_function<i_material * (__thiscall*)(void*, char const*, void*)>(this, 74)(this, material_name, vmt_key_values);
    }

    i_material* find_material(char const* material_name, const char* texture_group_name, bool complain = true, const char* complain_prefix = 0)
    {
        return memory::call_v_function<i_material*(__thiscall*)(void*, char const*, const char*, bool, const char*)>(this, 75)(this, material_name, texture_group_name, complain, complain_prefix);
    }

	c_mat_render_context* get_render_context()
	{
		return memory::call_v_function<c_mat_render_context*(__thiscall*)(void*)>(this, 102)(this);
	}

    void begin_render_target_allocation()
    {
        return memory::call_v_function<void(__thiscall*)(void*) >(this, 86)(this);
    }

    void end_render_target_allocation()
    {
        return memory::call_v_function<void(__thiscall*)(void*) >(this, 87)(this);
    }

    i_texture* create_named_render_target_texture_ex(const char* rt_name, int w, int h, render_target_size_mode_t render_target_size_mode, image_format_t image_format, material_render_target_depth_t MaterialRenderTargetDepth, unsigned int texture_flags, unsigned int render_target_flags)
    {
        return memory::call_v_function<i_texture * (__thiscall*)(void*, const char*, int, int, render_target_size_mode_t, image_format_t, material_render_target_depth_t, unsigned int, unsigned int)>(this, 89)(this, rt_name, w, h, render_target_size_mode, image_format, MaterialRenderTargetDepth, texture_flags, render_target_flags);
    }
};