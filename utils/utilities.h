#pragma once
#include <windows.h>

#include "../dependencies/xorstr/xorstr.h"
#include "../sdk/interfaces.h"
#include "../settings.h"

namespace utilities
{
	bool game_is_full_loaded();
	void attach_console();
	void detach_console();
	void run_javascript(void* html_panel, const char* script);
	const char* host_cleanup_con_var_string_value(const char* str);
	bool is_key_pressed(int key);
	int time_to_ticks(float time);
	float ticks_to_time(int ticks);
	float get_fov(const q_angle& from, const q_angle& to);
	bool screen_transform(const c_vector& in, c_vector* out);
	bool world_to_screen(const c_vector& in, c_vector* out);
	bool get_entity_box(c_base_entity* entity, box_t& box);
}