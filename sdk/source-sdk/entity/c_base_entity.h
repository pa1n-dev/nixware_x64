#pragma once

class c_base_entity
{
public:
	c_collideable* get_collidable()
	{
		return memory::call_v_function<c_collideable * (__thiscall*)(void*)>(this, 3)(this);
	}

	i_client_networkable* get_client_networkable()
	{
		return memory::call_v_function<i_client_networkable * (__thiscall*)(void*)>(this, 4)(this);
	}

	i_client_renderable* get_client_renderable()
	{
		return memory::call_v_function<i_client_renderable * (__thiscall*)(void*)>(this, 5)(this);
	}

	const c_vector& get_abs_origin()
	{
		return memory::call_v_function<c_vector & (__thiscall*)(void*)>(this, 9)(this);
	}

	//only works for local_player
	const q_angle& get_abs_angles()
	{
		return memory::call_v_function<c_vector & (__thiscall*)(void*)>(this, 10)(this);
	}

	int get_team_number()
	{
		return memory::call_v_function<int(__thiscall*)(void*)>(this, 77)(this);
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

	q_angle& eye_angles()
	{
		return memory::call_v_function<q_angle & (__thiscall*)(void*)>(this, 140)(this);
	}

	bool is_weapon()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 167)(this);
	}

	bool uses_lua()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 170)(this);
	}

	bool push_entity()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 172)(this);
	}

	uintptr_t get_owner_entity()
	{
		return ((uintptr_t)this + 0x734); //DT_GMOD_Player, Prop: m_hOwnerEntity
	}

	uintptr_t get_hands()
	{
		return ((uintptr_t)this + 0x38d0);  //DT_GMOD_Player, Prop: m_Hands
	}

	uintptr_t get_view_model()
	{
		return ((uintptr_t)this + 0x2da0); //DT_GMOD_Player, Prop: m_hViewModel[0]
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
		return *(int*)((uintptr_t)this + 0x440); //DT_GMOD_Player, Prop: m_fFlags
	}

	c_vector get_velocity()
	{
		return *(c_vector*)((uintptr_t)this + 0x148); //DT_GMOD_Player, Prop: m_vecVelocity
	}

	float get_simulation_time()
	{
		return *(float*)((uintptr_t)this + 0xA0); //DT_GMOD_Player, Prop: m_flSimulationTime
	}

	int get_tick_base()
	{
		return *(int*)((uintptr_t)this + 0x2d58); //DT_BasePlayer, Prop: m_nTickBase
	}

	int hitbox_set()
	{
		return *(int*)((uintptr_t)this + 0x16D8); //DT_GMOD_Player 0x16d8
	}

	bool& client_side_animation()
	{
		return *(bool*)((uintptr_t)this + 0x19d8); //DT_GMOD_Player, Prop: m_bClientSideAnimation, Offset: 0x19d8
	}

	q_angle& get_punch_angle()
	{
		return *(q_angle*)((uintptr_t)this + 0x2a08); //DT_GMOD_Player, Prop: m_vecPunchAngle,
	}

	//https://s10.gifyu.com/images/Sr48V.png
	c_hl2mp_player_anim_state* get_anim_state()
	{
		return *(c_hl2mp_player_anim_state**)((uintptr_t)this + 0x3620);
	}

	c_hl2mp_player_anim_state* create_anim_state()
	{
		using create_anim_state_fn = c_hl2mp_player_anim_state * (__cdecl*)(void*);

		static create_anim_state_fn create_anim_state = (create_anim_state_fn)memory::pattern_scanner(xorstr("client.dll"), xorstr("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 40 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B 1D ? ? ?"));

		if (!create_anim_state)
			throw;

		return create_anim_state(this);
	}

	void update_client_side_animations()
	{
		using update_client_side_animations_fn = void(__fastcall*)(void*);

		static update_client_side_animations_fn update_client_side_animations = (update_client_side_animations_fn)memory::pattern_scanner(xorstr("client.dll"), xorstr("48 83 EC 38 48 8B 0D ? ? ? ? 48 89 74 24 ? 48 89 7C 24 ?"));

		if (!update_client_side_animations)
			throw;

		update_client_side_animations(this);
	}

	void get_eye_position(c_vector& eye_position)
	{
		using get_eye_position_fn = void(__fastcall*)(void*, c_vector&);

		static get_eye_position_fn get_eye_position = (get_eye_position_fn)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("E8 ? ? ? ? 8B 08 89 0F 8B 48 04 89 4F 04 48 8B CB")), 1, 6);

		if (!get_eye_position)
			throw;

		get_eye_position(this, eye_position);
	}

	c_base_combat_weapon* get_active_weapon()
	{
		using get_active_weapon_fn = c_base_combat_weapon * (__fastcall*)(void*);

		static get_active_weapon_fn get_active_weapon = (get_active_weapon_fn)memory::pattern_scanner(xorstr("client.dll"), xorstr("40 53 48 83 EC 20 48 3B 0D ? ? ? ?"));

		if (!get_active_weapon)
			throw;

		return get_active_weapon(this);
	}

	void invalidate_bone_cache()
	{
		using invalidate_bone_cache_fn = void(__fastcall*)(void*);

		static invalidate_bone_cache_fn invalidate_bone_cache = (invalidate_bone_cache_fn)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("E8 ? ? ? ? 48 8B 06 8B D3")), 1, 6);

		if (!invalidate_bone_cache)
			throw;

		invalidate_bone_cache(this);
	}

	//https://s12.gifyu.com/images/SVJ0B.png
	void set_abs_origin(c_vector& origin)
	{
		using set_abs_origin_fn = void(__fastcall*)(void*, c_vector&);

		static set_abs_origin_fn set_abs_origin = (set_abs_origin_fn)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("E8 ? ? ? ? F3 41 0F 11 BF ? ? ? ?")), 1, 6);

		if (!set_abs_origin)
			throw;

		set_abs_origin(this, origin);
	}

	void set_abs_angles(q_angle& angles)
	{
		using set_abs_angles_fn = void(__fastcall*)(void*, q_angle&);

		static set_abs_angles_fn set_abs_angles = (set_abs_angles_fn)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("E8 ? ? ? ? 48 8D 57 70")), 1, 6);

		if (!set_abs_angles)
			throw;

		set_abs_angles(this, angles);
	}

	const char* get_class_name()
	{
		using get_class_name_fn = const char* (__fastcall*)(void*);

		static get_class_name_fn get_class_name = (get_class_name_fn)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("E8 ? ? ? ? 4D 8B 47 10")), 1, 6);

		if (!get_class_name)
			throw;

		return get_class_name(this);
	}
};
