#pragma once

class c_global_vars
{
public:
	float			realtime;
	int				framecount;
	float			absoluteframetime;
	float			curtime;
	float			frametime;
	int				max_clients;
	int				tickcount;
	float			interval_per_tick;
	float			interpolation_amount;
	int				sim_ticks_this_frame;
	int				network_protocol;

private:
	bool client;

public:
	bool remote_client;

private:
	int timestamp_networking_base;
	int timestamp_randomize_window;
};