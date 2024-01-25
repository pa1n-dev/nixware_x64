#pragma once

class i_view_render
{
public:
	const c_view_setup* get_view_setup()
	{
		return memory::call_v_function<const c_view_setup* (__thiscall*)(void*)>(this, 13)(this);
	}
};