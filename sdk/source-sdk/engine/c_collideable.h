#pragma once

class c_collideable
{
public:
	c_vector& mins()
	{
		return memory::call_v_function<c_vector&(__thiscall*)(void*)>(this, 1)(this);
	}

	c_vector& maxs()
	{
		return memory::call_v_function<c_vector&(__thiscall*)(void*)>(this, 2)(this);
	}
};
