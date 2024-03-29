#pragma once

//https://media.discordapp.net/attachments/1194221664339234816/1221895554347307129/image.png?ex=66143de9&is=6601c8e9&hm=f8826a7e1ce81a37cc0fe8a06443e1fbd2f61968c9e216d60cf272c28024327f&=&format=webp&quality=lossless
class c_client_state
{
public:
	char	pad_0000[0x20B68];
	float	last_server_ticktime;
	int		in_simulation;
	int		old_tick_count;
	float	tick_remainder;
	float	frametime;
	int		last_out_going_command;
	int		choked_commands;
	int		last_command_ack;
	int		command_ack;
};