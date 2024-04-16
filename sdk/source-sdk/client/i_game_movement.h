#pragma once

class c_move_data
{
public:
	char			pad0[4];
	unsigned int	player_handle;
	int				impulse;
	q_angle			view_angles;
	q_angle			abs_view_angles;
	int				buttons;
	int				old_buttons;
	float			forward_move;
	float			side_move;
	float			up_move;
	float			max_speed;
	float			client_max_speed;
	c_vector		velocity;
	q_angle			angles;
	q_angle			old_angles;
	float			step_height;
	c_vector		wish_velocity;
	c_vector		jump_velocity;
	c_vector		constraint_center;
	float			constraint_radius;
	float			constraint_width;
	float			constraint_speed_factor;
	c_vector		abs_origin;
};

class i_game_movement
{
public:
	void process_movement(c_base_entity* entity, c_move_data* move_data)
	{
		memory::call_v_function<void(__thiscall*)(void*, c_base_entity*, c_move_data*)>(this, 1)(this, entity, move_data);
	}

	void start_track_prediction_errors(c_base_entity* entity)
	{
		memory::call_v_function<void(__thiscall*)(void*, c_base_entity*)>(this, 2)(this, entity);
	}

	void finish_track_prediction_errors(c_base_entity* entity)
	{
		memory::call_v_function<void(__thiscall*)(void*, c_base_entity*)>(this, 3)(this, entity);
	}
};