#pragma once

class i_texture
{
public:
	const char* get_name()
	{
		return memory::call_v_function<const char*(__thiscall*)(void*)>(this, 0)(this);
	}
};