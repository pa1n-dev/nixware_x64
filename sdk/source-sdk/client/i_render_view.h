#pragma once

class i_render_view
{
public:
	void set_blend(float blend)
	{
		return memory::call_v_function<void(__thiscall*)(void*, float)>(this, 4)(this, blend);
	}

	float get_blend()
	{
		return memory::call_v_function<float(__thiscall*)(void*)>(this, 5)(this);
	}

	void set_color_modulation(float const* blend)
	{
		return memory::call_v_function<void(__thiscall*)(void*, float const*)>(this, 6)(this, blend);
	}

	void get_color_modulation(float* blend)
	{
		return memory::call_v_function<void(__thiscall*)(void*, float const*)>(this, 7)(this, blend);
	}

	void get_matrices_for_view(const c_view_setup& view, D3DMATRIX* world_to_view, D3DMATRIX* view_to_projection, D3DMATRIX* world_to_projection, D3DMATRIX* world_to_pixels)
	{
		return memory::call_v_function<void(__thiscall*)(void*, const c_view_setup&, D3DMATRIX*, D3DMATRIX*, D3DMATRIX*, D3DMATRIX*)>(this, 50)(this, view, world_to_view, view_to_projection, world_to_projection, world_to_pixels);
	}
};