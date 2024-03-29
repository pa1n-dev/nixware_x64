#pragma once

class c_base_entity
{
public:
	c_collideable* get_collidable()
	{
		return memory::call_v_function<c_collideable*(__thiscall*)(void*)>(this, 3)(this);
	}

	i_client_networkable* get_client_networkable()
	{
		return memory::call_v_function<i_client_networkable*(__thiscall*)(void*)>(this, 4)(this);
	}

	i_client_renderable* get_client_renderable()
	{
		return memory::call_v_function<i_client_renderable*(__thiscall*)(void*)>(this, 5)(this);
	}

	const c_vector& get_abs_origin()
	{
		return memory::call_v_function<c_vector&(__thiscall*)(void*)>(this, 9)(this);
	}

	//only works for local_player
	const q_angle& get_abs_angles()
	{
		return memory::call_v_function<c_vector&(__thiscall*)(void*)>(this, 10)(this);
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
		return memory::call_v_function<q_angle&(__thiscall*)(void*)>(this, 140)(this);
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

	c_vector get_velocity()
	{
		return *(c_vector*)((uintptr_t)this + 328);
	}

	float get_simulation_time() 
	{
		return *(float*)((uintptr_t)this + 0xA0);
	}

	int get_tick_base()
	{
		return *(int*)((uintptr_t)this + 0x2D50);
	}

	int hitbox_set()
	{
		return *(int*)((uintptr_t)this + 5848);
	}

	int& get_sequence()
	{
		return *(int*)((uintptr_t)this + 0x1A00);
	}

	float& get_cycle()
	{
		return *(float*)((uintptr_t)this + 0x1A08);
	}

	bool& client_side_animation()
	{
		return *(bool*)((uintptr_t)this + 0x19D0);
	}

	q_angle& get_punch_angle()
	{
		return *(q_angle*)((uintptr_t)this + 0x2A00);
	}

	c_studio_hdr* get_model_ptr()
	{
		return *(c_studio_hdr**)((uintptr_t)this + 0x1AF0);
	}

	unsigned int& hitbox_bone_cache_handle()
	{
		return *(unsigned int*)((uintptr_t)this + 0x1A98);
	}

	//https://media.discordapp.net/attachments/1194221664339234816/1214483423280889876/image.png?ex=65f946d4&is=65e6d1d4&hm=b41c877344e4b2bdb1f0d983962391b5eb7ab7f9d9776dbdbd1741725a1c18e8&=&format=webp&quality=lossless
	c_hl2mp_player_anim_state* get_anim_state()
	{
		return *(c_hl2mp_player_anim_state**)((uintptr_t)this + 0x3618);
	}

	c_hl2mp_player_anim_state* create_anim_state()
	{
		using create_anim_state_fn = c_hl2mp_player_anim_state*(__cdecl*)(void*);

		static create_anim_state_fn create_anim_state;

		if (!create_anim_state)
			create_anim_state = (create_anim_state_fn)memory::pattern_scanner(xorstr("client.dll"), xorstr("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 40 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B 1D ? ? ?"));

		return create_anim_state(this);
	}

	void update_client_side_animations()
	{
		using update_client_side_animations_fn = void(__fastcall*)(void*);

		static update_client_side_animations_fn update_client_side_animations;

		if (!update_client_side_animations)
			update_client_side_animations = (update_client_side_animations_fn)memory::pattern_scanner(xorstr("client.dll"), xorstr("48 83 EC 38 48 8B 0D ? ? ? ? 48 89 74 24 ? 48 89 7C 24 ?"));

		update_client_side_animations(this);
	}

	c_vector get_eye_position()
	{
		using get_eye_position_fn = void(__fastcall*)(void*, c_vector&);

		static get_eye_position_fn get_eye_position;

		if (!get_eye_position)
			get_eye_position = (get_eye_position_fn)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("E8 ? ? ? ? 8B 08 89 0F 8B 48 04 89 4F 04 48 8B CB")), 1, 6);

		c_vector vector;
		get_eye_position(this, vector);

		return vector;
	}

	c_base_combat_weapon* get_active_weapon()
	{
		using get_active_weapon_fn = c_base_combat_weapon* (__fastcall*)(void*);

		static get_active_weapon_fn get_active_weapon;

		if (!get_active_weapon)
			get_active_weapon = (get_active_weapon_fn)memory::pattern_scanner(xorstr("client.dll"), xorstr("40 53 48 83 EC 20 48 3B 0D ? ? ? ?"));

		return get_active_weapon(this);
	}

	void invalidate_bone_cache()
	{
		using invalidate_bone_cache_fn = void(__fastcall*)(void*);

		static invalidate_bone_cache_fn invalidate_bone_cache;

		if (!invalidate_bone_cache)
			invalidate_bone_cache = (invalidate_bone_cache_fn)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("E8 ? ? ? ? 48 8B 06 8B D3")), 1, 6);

		invalidate_bone_cache(this);
	}

	//https://cdn.discordapp.com/attachments/1194221664339234816/1209856472373137500/image.png?ex=65e871a5&is=65d5fca5&hm=0f8f3abe0ef4d35b2e97098c482c87b6d1c1a0ec7406dab4eb77fdd75205a9d2&
	void set_abs_origin(c_vector& origin)
	{
		using set_abs_origin_fn = void(__fastcall*)(void*, c_vector&);

		static set_abs_origin_fn set_abs_origin;

		if (!set_abs_origin)
			set_abs_origin = (set_abs_origin_fn)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("E8 ? ? ? ? F3 41 0F 11 BF ? ? ? ?")), 1, 6);

		set_abs_origin(this, origin);
	}

	void set_abs_angles(q_angle& angles)
	{
		using set_abs_angles_fn = void(__fastcall*)(void*, q_angle&);

		static set_abs_angles_fn set_abs_angles;

		if (!set_abs_angles)
			set_abs_angles = (set_abs_angles_fn)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("E8 ? ? ? ? 48 8D 57 70")), 1, 6);

		set_abs_angles(this, angles);
	}
};
