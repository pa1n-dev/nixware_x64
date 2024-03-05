#pragma once

class c_con_var
{
public:
	char pad_0000[8];
	void* next_con_var;
	bool registered;
	char pad_0014[4];
	char* name;
	char* help_string;
	uint32_t flags;
	char pad_002C[12];
	void* parent;
	char* default_value;
	char* string_value;
	uint32_t string_lenght;

public:
	float get_float()
	{
		return atof(string_value);
	}

	int get_int()
	{
		return atoi(string_value);
	}
};

class c_cvar
{
public:
	c_con_var* find_var(const char* var_name)
    {
        return memory::call_v_function<c_con_var* (__thiscall*)(void*, const char*)>(this, 17)(this, var_name);
    }
};