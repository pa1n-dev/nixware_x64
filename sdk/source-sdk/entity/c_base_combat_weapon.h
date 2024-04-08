#pragma once

class c_base_combat_weapon
{
public:
	bool uses_lua()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 170)(this);
	}

	bool push_entity()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 172)(this);
	}

	c_vector& get_bullet_spread()
	{
		return memory::call_v_function<c_vector&(__thiscall*)(void*)>(this, 325)(this);
	}

	const char* get_class_name()
	{
		return memory::call_v_function<const char*(__thiscall*)(void*)>(this, 367)(this);
	}

	int primary_ammo()
	{
		return *(int*)((uintptr_t)this + 0x1C48);
	}

	const char* get_name()
	{
		using  get_name_fn = const char* (__fastcall*)(void*);

		static get_name_fn get_name = (get_name_fn)memory::pattern_scanner(xorstr("client.dll"), xorstr("48 83 EC 28 0F B7 89 F4 1B 00 00 E8 ? ? ? ? 48 83 C0 0A"));

		if (!get_name)
			throw;

		return get_name(this);
	}

	const char* get_print_name()
	{
		using  get_print_name_t = const char* (__fastcall*)(void*);

		static get_print_name_t get_print_name = (get_print_name_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("48 83 EC 28 0F B7 89 F4 1B 00 00 E8 ? ? ? ? 48 83 C0 5A"));

		if (!get_print_name)
			throw;

		return get_print_name(this);
	}

	bool is_holding_tool()
	{
		char const* name = get_name();

		if (!strcmp(name, xorstr("weapon_physgun")) || !strcmp(name, xorstr("weapon_physcannon")))
			return true;

		return false;
	}

	bool is_without_spread()
	{
		char const* name = get_name();

		if (!strcmp(name, xorstr("weapon_357")) || !strcmp(name, xorstr("weapon_crossbow")) || !strcmp(name, xorstr("weapon_slam")) || !strcmp(name, xorstr("weapon_shotgun")))
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