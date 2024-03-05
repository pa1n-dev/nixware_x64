#pragma once

class i_client_networkable
{
public:
	size_t get_index()
	{
		return memory::call_v_function<size_t(__thiscall*)(void*)>(this, 9)(this);
	}
};