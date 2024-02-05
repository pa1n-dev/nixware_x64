#pragma once

class c_base_combat_weapon
{
public:
	bool push_entity()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 172)(this);
	}

	const char* get_class_name()
	{
		return memory::call_v_function<const char* (__thiscall*)(void*)>(this, 367)(this);
	}

	int primary_ammo()
	{
		return *(int*)((uintptr_t)this + 0x1C48);
	}

	const char* get_name()
	{
		using  get_name_t = const char* (__fastcall*)(void*);

		static get_name_t get_name;

		if (!get_name)
			get_name = (get_name_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("48 83 EC 28 0F B7 89 F4 1B 00 00 E8 ? ? ? ? 48 83 C0 0A"));

		return get_name(this);
	}

	const char* get_print_name()
	{
		using  get_print_name_t = const char* (__fastcall*)(void*);

		static get_print_name_t get_print_name;

		if (!get_print_name)
			get_print_name = (get_print_name_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("48 83 EC 28 0F B7 89 F4 1B 00 00 E8 ? ? ? ? 48 83 C0 5A"));

		return get_print_name(this);
	}

	bool is_holding_tool()
	{
		char const* name = get_name();

		if (!strcmp(name, "weapon_physgun") || !strcmp(name, "weapon_physcannon"))
			return true;

		return false;
	}

	bool can_shoot()
	{
		if (primary_ammo() > 0)
			return true;

		return false;
	}
};