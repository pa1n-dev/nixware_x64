#pragma once

typedef uint64_t v_panel;

class i_panel 
{
public:
	void set_key_board_input_enabled(v_panel panel, bool state)
	{
		return memory::call_v_function<void(__thiscall*)(void*, v_panel, bool)>(this, 31)(this, panel, state);
	}

	void set_mouse_input_enabled(v_panel panel, bool state)
	{
		return memory::call_v_function<void(__thiscall*)(void*, v_panel, bool)>(this, 32)(this, panel, state);
	}

	const char* get_name(v_panel idx)
	{
		return memory::call_v_function<const char* (__thiscall*)(void*, v_panel)>(this, 36)(this, idx);
	}
};