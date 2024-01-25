#pragma once

class c_user_cmd
{
public:
	int			command_number;
	int			tick_count;
	q_angle		view_angles;
	float		forward_move;
	float		side_move;
	float		up_move;
	int			buttons;
	char		impulse;
	int			weapon_select;
	int			weapon_subtype;
	int			random_seed;
	short		mouse_x;
	short		mouse_y;
	bool		has_been_predicted;
	char		buttons_pressed[5];
	char		scroll_wheel_speed;
	bool		world_clicking;
	c_vector	world_click_direction;
	bool		is_typing;
	c_vector	motion_sensor_positions[20];
	bool		forced;

public:
	crc32_t get_checksum() const
	{
		crc32_t crc{};

		crc32_init(&crc);
		crc32_process_buffer(&crc, &command_number, sizeof(command_number));
		crc32_process_buffer(&crc, &tick_count, sizeof(tick_count));
		crc32_process_buffer(&crc, &view_angles, sizeof(view_angles));
		crc32_process_buffer(&crc, &forward_move, sizeof(forward_move));
		crc32_process_buffer(&crc, &side_move, sizeof(side_move));
		crc32_process_buffer(&crc, &up_move, sizeof(up_move));
		crc32_process_buffer(&crc, &buttons, sizeof(buttons));
		crc32_process_buffer(&crc, &impulse, sizeof(impulse));
		crc32_process_buffer(&crc, &weapon_select, sizeof(weapon_select));
		crc32_process_buffer(&crc, &weapon_subtype, sizeof(weapon_subtype));
		crc32_process_buffer(&crc, &random_seed, sizeof(random_seed));
		crc32_process_buffer(&crc, &mouse_x, sizeof(mouse_x));
		crc32_process_buffer(&crc, &mouse_y, sizeof(mouse_y));
		crc32_process_buffer(&crc, &has_been_predicted, sizeof(has_been_predicted));
		crc32_process_buffer(&crc, &buttons_pressed, sizeof(buttons_pressed));
		crc32_process_buffer(&crc, &scroll_wheel_speed, sizeof(scroll_wheel_speed));
		crc32_process_buffer(&crc, &world_clicking, sizeof(world_clicking));
		crc32_process_buffer(&crc, &world_click_direction, sizeof(world_click_direction));
		crc32_process_buffer(&crc, &is_typing, sizeof(is_typing));
		crc32_process_buffer(&crc, &motion_sensor_positions, sizeof(motion_sensor_positions));
		crc32_process_buffer(&crc, &forced, sizeof(forced));
		crc32_final(&crc);

		return crc;
	}
};

class c_verified_user_cmd
{
public:
	c_user_cmd  m_cmd;
	int			m_crc;
};