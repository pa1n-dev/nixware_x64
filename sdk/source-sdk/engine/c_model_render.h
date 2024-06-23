#pragma once

enum override_type_t
{
	override_normal = 0,
	override_build_shadows,
	override_depth_write,
	override_ssao_depth_write,
};

class c_model_render
{
public:
	void forced_material_override(i_material* material, override_type_t override_type = override_normal)
	{
		return memory::call_v_function<void(__thiscall*)(void*, i_material*, override_type_t)>(this, 1)(this, material, override_type);
	}

	void setup_lighting(const c_vector& center)
	{
		return memory::call_v_function<void(__thiscall*)(void*, const c_vector&)>(this, 21)(this, center);
	}

	void suppress_engine_lighting(bool suppress)
	{
		return memory::call_v_function<void(__thiscall*)(void*, bool)>(this, 23)(this, suppress);
	}
};