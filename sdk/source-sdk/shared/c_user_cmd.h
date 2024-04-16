#pragma once

typedef unsigned int crc32_t;

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
	crc32_t get_check_sum()
	{
		using get_check_sum_fn = crc32_t(__fastcall*)(void*);
		static get_check_sum_fn get_check_sum = (get_check_sum_fn)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("E8 ? ? ? ? 44 8B C8 B8 ? ? ? ?")), 1, 5);

		if (!get_check_sum)
			throw;

		return get_check_sum(this);
	}
};

class c_verified_user_cmd
{
public:
	void set_user_cmd(c_user_cmd* cmd)
	{
		m_cmd = *cmd;
		m_crc = cmd->get_check_sum();
	}

	c_user_cmd		m_cmd;
	crc32_t			m_crc;
};