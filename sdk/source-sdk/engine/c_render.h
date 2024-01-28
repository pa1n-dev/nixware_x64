#pragma once

class c_render
{
public:
	const D3DMATRIX& world_to_screen_matrix()
	{
		return memory::call_v_function<const D3DMATRIX & (__thiscall*)(void*)>(this, 13)(this);
	}
};