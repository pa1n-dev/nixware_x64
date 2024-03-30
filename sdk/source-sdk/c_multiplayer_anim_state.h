#pragma once

class c_base_entity;

struct multi_player_movement_data_t
{
	float walk_speed;
	float run_speed;
	float sprint_speed;
	float body_yaw_rate;
};

class c_multiplayer_anim_state
{
public:
	void destructor()
	{
		memory::call_v_function<void(__thiscall*)(void*)>(this, 0)(this);
	}

	void update(float yaw, float pitch)
	{
		return memory::call_v_function<void(__thiscall*)(void*, float, float)>(this, 4)(this, yaw, pitch);
	}

	void init(c_base_entity* entity, multi_player_movement_data_t& movement_data)
	{
		return memory::call_v_function<void(__thiscall*)(void*, c_base_entity*, multi_player_movement_data_t&)>(this, 12)(this, entity, movement_data);
	}
};
