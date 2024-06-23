#pragma once

class c_entity_list
{
public:
	c_base_entity* get_entity(int index)
	{
		return memory::call_v_function<c_base_entity*(__thiscall*)(void*, int)>(this, 3)(this, index);
	}

	c_base_entity* get_entity_from_handle(uintptr_t pointer)
	{
		return memory::call_v_function<c_base_entity * (__thiscall*)(void*, uintptr_t)>(this, 4)(this, pointer);
	}

	size_t get_highest_entity_index()
	{
		return memory::call_v_function<size_t(__thiscall*)(void*)>(this, 6)(this);
	}
};