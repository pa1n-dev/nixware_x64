#pragma once

class c_base_entity
{
public:
	c_collideable* get_collidable()
	{
		return memory::call_v_function<c_collideable* (__thiscall*)(void*)>(this, 3)(this);
	}

	c_vector& get_render_origin()
	{
		return memory::call_v_function<c_vector& (__thiscall*)(void*)>(this, 9)(this);
	}

	bool is_alive()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 129)(this);
	}

	bool is_player()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 130)(this);
	}

	bool is_dormant()
	{
		return *(bool*)((uintptr_t)this + 0x1FA);
	}
};