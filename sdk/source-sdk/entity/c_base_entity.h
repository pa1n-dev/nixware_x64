#pragma once

class c_base_entity
{
public:
	c_collideable* get_collidable()
	{
		return memory::call_v_function<c_collideable * (__thiscall*)(void*)>(this, 3)(this);
	}

	i_client_renderable* get_client_renderable()
	{
		return memory::call_v_function<i_client_renderable * (__thiscall*)(void*)>(this, 5)(this);
	}

	c_vector& get_render_origin()
	{
		return memory::call_v_function<c_vector & (__thiscall*)(void*)>(this, 9)(this);
	}

	int get_health()
	{
		return memory::call_v_function<int(__thiscall*)(void*)>(this, 108)(this);
	}

	bool is_alive()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 129)(this);
	}

	bool is_player()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 130)(this);
	}

	bool push_entity()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 172)(this);
	}

	bool is_dormant()
	{
		return *(bool*)((uintptr_t)this + 0x1FA);
	}

	int get_move_type()
	{
		return *(int*)((uintptr_t)this + 0x1F4);
	}

	int get_flags()
	{
		return *(int*)((uintptr_t)this + 0x440);
	}

	q_angle& get_punch_angle()
	{
		return *(q_angle*)((uintptr_t)this + 0x2A00);
	}

	c_vector get_eye_position()
	{
		using get_eye_position_t = void(__fastcall*)(void*, c_vector&);

		static get_eye_position_t get_eye_position;

		if (!get_eye_position)
			get_eye_position = (get_eye_position_t)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("E8 ? ? ? ? 8B 08 89 0F 8B 48 04 89 4F 04 48 8B CB")), 1, 6);

		c_vector vector;
		get_eye_position(this, vector);

		return vector;
	}

	c_base_combat_weapon* get_active_weapon()
	{
		using get_active_weapon_t = c_base_combat_weapon* (__fastcall*)(void*);

		static get_active_weapon_t get_active_weapon;

		if (!get_active_weapon)
			get_active_weapon = (get_active_weapon_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("40 53 48 83 EC 20 48 3B 0D ? ? ? ?"));

		return get_active_weapon(this);
	}
};
