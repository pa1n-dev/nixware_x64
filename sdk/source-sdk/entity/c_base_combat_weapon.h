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
		return memory::call_v_function<c_vector & (__thiscall*)(void*)>(this, 325)(this);
	}

	const char* get_name()
	{
		return memory::call_v_function<const char* (__thiscall*)(void*)>(this, 366)(this);
	}

	const char* get_print_name()
	{
		return memory::call_v_function<const char* (__thiscall*)(void*)>(this, 367)(this);
	}

	int primary_ammo()
	{
		return *(int*)((uintptr_t)this + 0x1C50); /*m_iClip1*/
	}

	float next_primary_attack()
	{
		return *(float*)((uintptr_t)this + 0x1C04); /*m_flNextPrimaryAttack*/
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

	bool can_fire()
	{
		if (primary_ammo() <= 0)
			return false;

		return true;
	}
};