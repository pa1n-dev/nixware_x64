#pragma once

class c_collidable
{
public:
	c_vector& mins()
	{
		return memory::call_v_function<c_vector& (__thiscall*)(void*)>(this, 1)(this);
	}

	c_vector& maxs()
	{
		return memory::call_v_function<c_vector& (__thiscall*)(void*)>(this, 2)(this);
	}
};

class c_base_entity
{
public:
	c_collidable* get_collidable()
	{
		return memory::call_v_function<c_collidable* (__thiscall*)(void*)>(this, 3)(this);
	}

	c_vector& get_render_origin()
	{
		return memory::call_v_function<c_vector& (__thiscall*)(void*)>(this, 9)(this);
	}

	bool is_dormant()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 48)(this);
	}

	bool is_alive()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 129)(this);
	}

	bool is_player()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 130)(this);
	}
};