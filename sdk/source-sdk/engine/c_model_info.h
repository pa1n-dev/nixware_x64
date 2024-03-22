#pragma once

struct model_render_info_t
{
    c_vector				origin;
    q_angle				    angles;
    i_client_renderable*    renderable;
    const void*             model;
    const matrix3x4*        model_to_world;
    const matrix3x4*        lighting_offset;
    const c_vector*         lighting_origin;
    int					    flags;
    int					    entity_index;
    int					    skin;
    int					    body;
    int					    hitbox_set;
    void*                   instance;

    model_render_info_t()
    {
        model_to_world = NULL;
        lighting_offset = NULL;
        lighting_origin = NULL;
    }
};

class c_model_info
{
public:
	studiohdr_t* get_studio_model(void* model)
	{
		return memory::call_v_function<studiohdr_t* (__thiscall*)(void*, void*)>(this, 28)(this, model);
	}
};