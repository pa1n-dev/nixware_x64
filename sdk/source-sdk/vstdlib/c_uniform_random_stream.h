#pragma once

class c_uniform_random_stream
{
public:
	void set_seed(int seed)
	{
		return memory::call_v_function<void(__thiscall*)(void*, int)>(this, 0)(this, seed);
	}

	float random_float(float min = 0.0f, float max = 1.0f)
	{
		return memory::call_v_function<float(__thiscall*)(void*, float, float)>(this, 1)(this, min, max);
	}

	int random_int(int min = 0, int max = 1)
	{
		return memory::call_v_function<int(__thiscall*)(void*, int, int)>(this, 2)(this, min, max);
	}
};