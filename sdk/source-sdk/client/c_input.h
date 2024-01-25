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
	GAME_AXIS_NONE = 0,
	GAME_AXIS_FORWARD,
	GAME_AXIS_PITCH,
	GAME_AXIS_SIDE,
	GAME_AXIS_YAW,
	MAX_GAME_AXES
};

enum
{
	MOUSE_ACCEL_THRESHHOLD1 = 0,
	MOUSE_ACCEL_THRESHHOLD2,
	MOUSE_SPEED_FACTOR,
	NUM_MOUSE_PARAMS,
};

class c_input
{
public:
	virtual void			init_all();
	virtual void			shutdown_all();
	virtual int				get_button_bits(int);
	virtual void			create_move(int sequence_number, float input_sample_frametime, bool active);
	virtual void			extra_mouse_sample(float frametime, bool active);
	virtual bool			write_usercmd_delta_to_buffer(void* buf, int from, int to, bool is_new_command);
	virtual void			encode_usercmd_to_buffer(void*& buf, int slot);
	virtual void			decode_usercmd_from_buffer(void*& buf, int slot);
	virtual void*			get_usercmd(int sequence_number);
	virtual void			make_weapon_selection(void* weapon);
	virtual float			key_state(int32_t* key);
	virtual int				key_event(int down, int32_t keynum, const char* psz_current_binding);
	virtual void*			find_key(const char* name);
	virtual void			controller_commands(void);
	virtual void			joystick_advanced(void);
	virtual void			joystick_set_sample_time(float frametime);
	virtual void			in_set_sample_time(float frametime);
	virtual void			accumulate_mouse(void);
	virtual void			activate_mouse(void);
	virtual void			deactivate_mouse(void);
	virtual void			clear_states(void);
	virtual float			get_look_spring(void);
	virtual void			get_fullscreen_mouse_pos(int* mx, int* my, int* unclampedx = NULL, int* unclampedy = NULL);
	virtual void			set_fullscreen_mouse_pos(int mx, int my);
	virtual void			reset_mouse(void);
	virtual float			get_last_forward_move(void);
	virtual float			joystick_get_forward(void);
	virtual float			joystick_get_side(void);
	virtual float			joystick_get_pitch(void);
	virtual float			joystick_get_yaw(void);
	virtual void			clear_input_button(int bits);
	virtual void			cam_think(void);
	virtual int				cam_is_third_person(void);
	virtual void			cam_to_third_person(void);
	virtual void			cam_to_first_person(void);
	virtual void			cam_start_mouse_move(void);
	virtual void			cam_end_mouse_move(void);
	virtual void			cam_start_distance(void);
	virtual void			cam_end_distance(void);
	virtual int				cam_intercepting_mouse(void);
	virtual void			cam_to_orthographic();
	virtual bool			cam_is_orthographic() const;
	virtual void			cam_orthographic_size(float& w, float& h) const;
	virtual float			cam_cap_yaw(float f_val);

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
	int						orig_mouse_parms[NUM_MOUSE_PARAMS];
	int						new_mouse_parms[NUM_MOUSE_PARAMS];
	bool					check_mouse_param[NUM_MOUSE_PARAMS];
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