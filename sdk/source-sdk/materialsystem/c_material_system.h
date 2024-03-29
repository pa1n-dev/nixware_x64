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
	c_mat_render_context* get_render_context()
	{
		return memory::call_v_function<c_mat_render_context*(__thiscall*)(void*)>(this, 102)(this);
	}
};