#pragma once

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
};

class c_material_system
{
public:
    i_material* find_material(char const* material_name, const char* texture_group_name, bool complain = true, const char* complain_prefix = 0)
    {
        return memory::call_v_function<i_material*(__thiscall*)(void*, char const*, const char*, bool, const char*)>(this, 75)(this, material_name, texture_group_name, complain, complain_prefix);
    }

	c_mat_render_context* get_render_context()
	{
		return memory::call_v_function<c_mat_render_context*(__thiscall*)(void*)>(this, 102)(this);
	}
};