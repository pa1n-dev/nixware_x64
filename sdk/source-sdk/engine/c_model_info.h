#pragma once

class c_model_info
{
public:
	studiohdr_t* get_studio_model(void* model)
	{
		return memory::call_v_function<studiohdr_t* (__thiscall*)(void*, void*)>(this, 28)(this, model);
	}
};