#include "lag_compensation.h"

//https://media.discordapp.net/attachments/1194221664339234816/1214847464277024768/image.png?ex=65fa99de&is=65e824de&hm=0d881e116dd3a29aaf32d926899891343d2fce9aa895e54b0c865aa28eaaad6d&=&format=webp&quality=lossless
const char* host_cleanup_con_var_string_value(const char* str)
{
	using host_cleanup_con_var_string_value_t = const char*(*)(const char*);

	static host_cleanup_con_var_string_value_t host_cleanup_con_var_string_value;

	if (!host_cleanup_con_var_string_value)
		host_cleanup_con_var_string_value = (host_cleanup_con_var_string_value_t)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("engine.dll"), xorstr("E8 ? ? ? ? 48 8B 16 48 8B CE 48 8B F8")), 1, 6);

	return host_cleanup_con_var_string_value(str);
}

void lag_compensation::write_user_cmd_delta_to_buffer_callback()
{
	if (has_to_reset)
		return reset_values();

	if (!has_to_change)
		return;

	c_net_channel* net_channel = interfaces::engine->get_net_channel_info();
	if (!net_channel)
		return;

	{
		NET_SetConVar net_interpolate("cl_interpolate", interpolate == 0 ? "0" : "1");
		net_channel->send_net_msg(net_interpolate, true);
	}

	{
		char buf[64];
		sprintf_s(buf, "%f", interp);

		NET_SetConVar net_interp("cl_interp", host_cleanup_con_var_string_value(buf));
		net_channel->send_net_msg(net_interp, true);
	}

	{
		char buf[64];
		sprintf_s(buf, "%f", ratio);

		NET_SetConVar cl_interp_ratio("cl_interp_ratio", host_cleanup_con_var_string_value(buf));
		net_channel->send_net_msg(cl_interp_ratio, true);
	}

	has_to_change = false;
	has_to_reset = true;
}

void lag_compensation::reset_values()
{
	c_con_var* cl_interpolate = interfaces::cvar->find_var("cl_interpolate");
	c_con_var* cl_interp = interfaces::cvar->find_var("cl_interp");
	c_con_var* cl_interp_ratio = interfaces::cvar->find_var("cl_interp_ratio");

	c_net_channel* net_channel = interfaces::engine->get_net_channel_info();
	if (!net_channel)
		return;

	{
		NET_SetConVar net_interpolate("cl_interpolate", cl_interpolate->get_int() == 0 ? "0" : "1");
		net_channel->send_net_msg(net_interpolate, true);
	}

	{
		char buf[64];
		sprintf_s(buf, "%f", cl_interp->get_float());

		NET_SetConVar net_interp("cl_interp", host_cleanup_con_var_string_value(buf));
		net_channel->send_net_msg(net_interp, true);
	}

	{
		char buf[64];
		sprintf_s(buf, "%f", cl_interp_ratio->get_float());

		NET_SetConVar cl_interp_ratio("cl_interp_ratio", host_cleanup_con_var_string_value(buf));
		net_channel->send_net_msg(cl_interp_ratio, true);
	}

	reset_ticks = 3;
	has_to_reset = false;
}

void lag_compensation::update_desired_values(bool _interpolate, float _interp, float _ratio)
{
	static c_con_var* cl_interp = interfaces::cvar->find_var("cl_interp");
	static c_con_var* cl_interp_ratio = interfaces::cvar->find_var("cl_interp_ratio");

	interpolate = _interpolate;

	interp = _interp;

	if (interp == -1.f)
		interp = cl_interp->get_float();

	ratio = _ratio;

	if (ratio == -1.f)
		ratio = cl_interp_ratio->get_float();

	has_to_change = true;
}

/*void lag_compensation::cancel_updates()
{
	has_to_change = false;
}*/

bool lag_compensation::get_is_locked()
{
	static int last_tick_count = 0;
	if (!has_to_reset && reset_ticks > 0 && last_tick_count != interfaces::global_vars->tick_count)
	{
		last_tick_count = interfaces::global_vars->tick_count;

		reset_ticks--;
	}

	return (has_to_reset || reset_ticks > 0  );
}