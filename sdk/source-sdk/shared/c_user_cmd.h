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
	bool		is_world_clicking;
	c_vector	world_click_direction;
	bool		is_typing;
	c_vector	motion_sensor_positions[20];
	bool		forced;

public:
	//https://media.discordapp.net/attachments/1194221664339234816/1211398926536540251/image.png?ex=65ee0e2a&is=65db992a&hm=8e22e874ad2032183f553e690226f9417e2bda58afff099a0407f7b8b16c54be&=&format=webp&quality=lossless
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
		crc32_final(&crc);

		return crc;
	}
};

class c_verified_user_cmd
{
public:
	c_user_cmd		m_cmd;
	crc32_t			m_crc;
};