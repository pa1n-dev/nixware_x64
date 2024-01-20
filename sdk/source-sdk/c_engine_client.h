#pragma once

typedef struct player_info_s
{
	char			name[128];
	int				user_id;
	char			guid[32 + 1];
	unsigned int	friends_id;
	char			friends_name[128];
	bool			is_fake_player;
	bool			is_hltv;
	unsigned int	custom_files[4];
	unsigned char	files_downloaded;
} player_info_t;

class c_engine_client
{
public:
	void get_screen_size(int& width, int& height)
	{
		return memory::call_v_function<void(__thiscall*)(void*, int&, int&)>(this, 5)(this, width, height);
	}

	bool get_player_info(int index, player_info_t* info)
	{
		return memory::call_v_function<bool(__thiscall*)(void*, int, player_info_t*)>(this, 8)(this, index, info);
	}

	int get_local_player()
	{
		return memory::call_v_function<int(__thiscall*)(void*)>(this, 12)(this);
	}

	bool is_in_game()
	{
		return memory::call_v_function<bool(__thiscall*)(void*)>(this, 26)(this);
	}
};