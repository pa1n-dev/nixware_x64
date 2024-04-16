#pragma once

struct camera_third_data_t
{
	float		pitch;
	float		yaw;
	float		dist;
	float		lag;
	c_vector	hull_min;
	c_vector	hull_max;
};

struct joy_axis_t
{
	unsigned int axis_flags;
	unsigned int axis_map;
	unsigned int control_map;
};

enum
{
	game_axis_none = 0,
	game_axis_forward,
	game_axis_pitch,
	game_axis_side,
	game_axis_yaw,
	max_game_axes
};

enum
{
	mouse_accel_threshhold1 = 0,
	mouse_accel_threshhold2,
	mouse_speed_factor,
	num_mouse_params,
};

class c_input
{
public:
	c_user_cmd* get_user_cmd(int sequence_number)
	{
		return cmds + (sequence_number % MULTIPLAYER_BACKUP);
	}

	c_verified_user_cmd* get_verified_user_cmd(int sequence_number)
	{
		return verified_cmds + (sequence_number % MULTIPLAYER_BACKUP);
	}

	char                    pad[8];
	bool					mouse_initialized;
	bool					mouse_active;
	bool					joystick_advanced_init;
	bool					had_joysticks;
	float					accumulated_mouse_x_movement;
	float					accumulated_mouse_y_movement;
	float					previous_mouse_x_position;
	float					previous_mouse_y_position;
	float					remaining_joystick_sample_time;
	float					keyboard_sample_time;
	bool					restore_spi;
	int						orig_mouse_parms[num_mouse_params];
	int						new_mouse_parms[num_mouse_params];
	bool					check_mouse_param[num_mouse_params];
	bool					mouse_parms_valid;
	joy_axis_t				axes[6];
	void*					keys;
	bool					camera_intercepting_mouse;
	bool					camera_in_third_person;
	bool					camera_moving_with_mouse;
	bool					camera_distance_move;
	int						camera_old_x;
	int						camera_old_y;
	int						camera_x;
	int						camera_y;
	bool					camera_is_orthographic;
	q_angle					previous_view_angles;
	float					last_forward_move;
	float					previous_joystick_forward;
	float					previous_joystick_side;
	float					previous_joystick_pitch;
	float					previous_joystick_yaw;
	c_user_cmd*				cmds;
	c_verified_user_cmd*	verified_cmds;
	camera_third_data_t*	camera_third_data;
};