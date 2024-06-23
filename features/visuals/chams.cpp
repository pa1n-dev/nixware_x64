#include "chams.h"

i_material* chams::create_material(const char* name, bool flat, bool wireframe, bool add_shine)
{
    std::string material_data = std::format(R"("{}"
    {{
        "$basetexture" "vgui/white_additive"
        "$envmap" "{}"
        "$normalmapalphaenvmapmask" "{}"
        "$envmapcontrast" "{}"
        "$model" "1"
        "$flat" "1"
        "$nocull" "0"
        "$selfillum" "1"
        "$halflambert" "1"
        "$nofog" "0"
        "$ignorez" "0"
        "$znearer" "0"
        "$wireframe" "{}"
    }}
    )", flat || wireframe ? "UnlitGeneric" : "VertexLitGeneric", add_shine ? "env_cubemap" : "", add_shine ? 1 : 0, add_shine ? 1 : 0, wireframe ? 1 : 0);

    void* kv = key_values::key_values();
    if (!kv)
        return nullptr;

    key_values::initialize(kv, name);
    if (!key_values::load_from_buffer(kv, name, material_data.c_str()))
        return nullptr;

    i_material* created_material = interfaces::material_system->create_material(name, kv);
    if (!created_material)
        return nullptr;

    created_material->increment_reference_count();

    return created_material;
}

void chams::push_material_override(float color[4], int material_type)
{
    static i_material* textured = chams::create_material(xorstr("textured_material"), false, false, false);
    static i_material* metal = chams::create_material(xorstr("metal_material"), false, false, true);
    static i_material* wireframe = chams::create_material(xorstr("wireframe_material"), false, true, false);
    static i_material* flat = chams::create_material(xorstr("flat_material"), true, false, false);

    if (!textured || !metal || !wireframe || !flat)
        return;

    interfaces::model_render->suppress_engine_lighting(true);
    interfaces::model_render->setup_lighting(c_vector());

    interfaces::render_view->set_color_modulation(color);
    interfaces::render_view->set_blend(color[3]);

    i_material* material = nullptr;
    switch (material_type)
    {
    case 0:
        material = textured;
        break;
    case 1:
        material = metal;
        break;
    case 2:
        material = wireframe;
        break;
    case 3:
        material = flat;
        break;
    case 4:
        break;
    }

    interfaces::model_render->forced_material_override(material);
}

void chams::pop_material_override()
{
    static float clear_color[3] = { 1.f, 1.f, 1.f };

    interfaces::model_render->suppress_engine_lighting(false);

    interfaces::render_view->set_color_modulation(clear_color);
    interfaces::render_view->set_blend(1.f);

    interfaces::model_render->forced_material_override(nullptr);
}

void chams::push_ignore_z(bool ignore_z)
{
    c_mat_render_context* render_context = interfaces::material_system->get_render_context();
    if (!render_context)
        return;

    if (ignore_z)
        render_context->depth_range(0.f, 0.f);
}

void chams::pop_ignore_z()
{
    c_mat_render_context* render_context = interfaces::material_system->get_render_context();
    if (!render_context)
        return;

    render_context->depth_range(0.f, 1.f);
}