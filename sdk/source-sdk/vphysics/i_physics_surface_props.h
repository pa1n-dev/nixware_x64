#pragma once

class surface_data_t
{
public:
    char    pad_0000[96];
    int     material;
};

class i_physics_surface_props
{
public:
    surface_data_t* get_surface_data(int surface_data_index)
    {
        return memory::call_v_function<surface_data_t * (__thiscall*)(void*, int)>(this, 5)(this, surface_data_index);
    }
};