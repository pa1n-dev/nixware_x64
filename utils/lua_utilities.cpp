#include "lua_utilities.h"

const char* lua_utilities::get_name(c_base_entity* entity)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return "";

	entity->push_entity();

	lua->get_field(-1, xorstr("GetName"));
	if (!lua->is_type(-1, object_type_t::function))
	{
		lua->pop(2);
		return get_rank_table_name(entity);
	}

	lua->push(-2);
	lua->call(1, 1);

	const char* value = lua->get_string(-1);
	lua->pop(2);

	return value;
}

const char* lua_utilities::get_user_group(c_base_entity* entity)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return "";

	entity->push_entity();

	lua->get_field(-1, xorstr("GetUserGroup"));
	if (!lua->is_type(-1, object_type_t::function))
	{
		lua->pop(2);
		return get_rank_table_name(entity);
	}

	lua->push(-2);
	lua->call(1, 1);

	const char* value = lua->get_string(-1);
	lua->pop(2);

	return value;
}

//https://s9.gifyu.com/images/SVyPi.png (RusEliteRp)
const char* lua_utilities::get_rank_table_name(c_base_entity* entity)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return "";

	entity->push_entity();

	lua->get_field(-1, xorstr("GetRankTable"));
	if (!lua->is_type(-1, object_type_t::function))
	{
		lua->pop(2);
		return "";
	}

	lua->push(-2);
	lua->call(1, 1);

	lua->get_field(-1, xorstr("NiceName"));
	if (!lua->is_type(-1, object_type_t::string))
	{
		lua->pop(3);
		return "";
	}

	const char* value = lua->get_string(-1);

	lua->pop(3);

	return value;
}

//https://s9.gifyu.com/images/SVGKk.png (RusEliteRp)
const char* lua_utilities::get_rp_jobs_list(int team)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return "";

	lua->push_special(lua_special_glob);

	lua->get_field(-1, xorstr("rp"));
	if (!lua->is_type(-1, object_type_t::table))
	{
		lua->pop(2);
		return "";
	}

	lua->get_field(-1, xorstr("jobs"));
	if (!lua->is_type(-1, object_type_t::table))
	{
		lua->pop(3);
		return "";
	}

	lua->get_field(-1, xorstr("List"));
	if (!lua->is_type(-1, object_type_t::table))
	{
		lua->pop(4);
		return "";
	}

	lua->push_number(team);
	lua->get_table(-2);
	if (!lua->is_type(-1, object_type_t::table))
	{
		lua->pop(5);
		return "";
	}

	lua->get_field(-1, xorstr("Name"));
	if (!lua->is_type(-1, object_type_t::string))
	{
		lua->pop(6);
		return "";
	}

	const char* value = lua->get_string(-1);
	lua->pop(6);

	return value;
}

//RusEliteRp
int lua_utilities::get_job_without_disguise(c_base_entity* entity)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return -1;

	lua->push_special(lua_special_glob);
	lua->get_field(-1, xorstr("rp"));
	if (!lua->is_type(-1, object_type_t::table))
	{
		lua->pop(2);
		return -1;
	}

	lua->get_field(-1, xorstr("GetJobWithoutDisguise"));
	if (!lua->is_type(-1, object_type_t::function))
	{
		lua->pop(3);
		return -1;
	}

	lua->push_number(entity->get_client_networkable()->get_index());
	lua->call(1, 1);

	if (!lua->is_type(-1, object_type_t::number))
	{
		lua->pop(3);
		return -1;
	}

	int value = lua->get_number(-1);
	lua->pop(3);

	return value;
}

const char* lua_utilities::get_team_name(c_base_entity* entity)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return "";

	int team = get_job_without_disguise(entity);
	if (team != -1)
		return get_rp_jobs_list(team);

	lua->push_special(lua_special_glob);

	lua->get_field(-1, xorstr("team"));
	if (!lua->is_type(-1, object_type_t::table))
	{
		lua->pop(2);
		return "";
	}

	lua->get_field(-1, xorstr("GetName"));
	if (!lua->is_type(-1, object_type_t::function))
	{
		lua->pop(3);
		return "";
	}

	lua->push_number(entity->get_team_number());
	lua->call(1, 1);

	const char* value = lua->get_string(-1);
	lua->pop(3);

	return value;
}

const char* lua_utilities::get_weapon_print_name(c_base_combat_weapon* weapon)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return "";

	if (!weapon->uses_lua())
		return weapon->get_print_name();

	weapon->push_entity();

	lua->get_field(-1, xorstr("PrintName"));
	if (!lua->is_type(-1, object_type_t::string))
	{
		lua->pop(2);
		return "";
	}

	const char* value = lua->get_string(-1);
	lua->pop(2);

	return value;
}

const char* lua_utilities::get_weapon_base(c_base_combat_weapon* weapon)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return "";

	if(!weapon->uses_lua())
		return "";

	weapon->push_entity();

	lua->get_field(-1, xorstr("Base"));
	if (!lua->is_type(-1, object_type_t::string))
	{
		lua->pop(2);
		return "";
	}

	const char* value = lua->get_string(-1);
	lua->pop(2);

	return value;
}

float lua_utilities::get_m9k_spread(c_user_cmd* cmd, c_base_combat_weapon* weapon)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return 0.f;

	if (!weapon->uses_lua())
		return 0.f;

	weapon->push_entity();

	lua->get_field(-1, xorstr("Primary"));
	if (!lua->is_type(-1, object_type_t::table))
	{
		lua->pop(2);
		return 0.f;
	}

	if (cmd->buttons & IN_ATTACK2)
	{
		lua->get_field(-1, xorstr("IronAccuracy"));
		if (!lua->is_type(-1, object_type_t::number))
		{
			lua->pop(3);
			return 0.f;
		}
	}
	else
	{
		lua->get_field(-1, xorstr("Spread"));
		if (!lua->is_type(-1, object_type_t::number))
		{
			lua->pop(3);
			return 0.f;
		}
	}

	double value = lua->get_number(-1);
	lua->pop(3);

	return value;
}

float lua_utilities::get_ptp_spread(c_base_combat_weapon* weapon)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return 0.f;

	if (!weapon->uses_lua())
		return 0.f;

	weapon->push_entity();

	lua->get_field(-1, xorstr("Primary"));
	if (!lua->is_type(-1, object_type_t::table))
	{
		lua->pop(2);
		return 0.f;
	}

	lua->get_field(-1, xorstr("Cone"));
	if (!lua->is_type(-1, object_type_t::number))
	{
		lua->pop(3);
		return 0.f;
	}

	double value = lua->get_number(-1);
	lua->pop(3);

	return value;
}

float lua_utilities::get_weapon_max_spread_inc(c_base_combat_weapon* weapon)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return 0.f;

	if (!weapon->uses_lua())
		return 0.f;

	weapon->push_entity();

	lua->get_field(-1, xorstr("MaxSpreadInc"));
	if (!lua->is_type(-1, object_type_t::number))
	{
		lua->pop(2);
		return 0.f;
	}

	float value = lua->get_number(-1);

	lua->pop(2);

	return value;
}

float lua_utilities::get_weapon_cur_cone(c_base_combat_weapon* weapon)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return 0.f;

	if (!weapon->uses_lua())
		return 0.f;

	weapon->push_entity();

	lua->get_field(-1, xorstr("CurCone"));
	if (!lua->is_type(-1, object_type_t::number))
	{
		lua->pop(2);
		return 0.f;
	}

	float value = lua->get_number(-1);

	lua->pop(2);

	return value;
}

//https://s12.gifyu.com/images/SaM2m.png
bool lua_utilities::build_m9k_info(c_base_combat_weapon* weapon, m9k_info& info)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return false;

	if (!weapon->uses_lua())
		return false;

	weapon->push_entity();

	lua->get_field(-1, xorstr("Primary"));
	if (!lua->is_type(-1, object_type_t::table))
	{
		lua->pop(2);
		return false;
	}

	lua->get_field(-1, xorstr("Damage"));
	if (!lua->is_type(-1, object_type_t::number))
	{
		lua->pop(3);
		return false;
	}

	info.damage = lua->get_number(-1);
	lua->pop();

	lua->get_field(-1, xorstr("Ammo"));
	if (!lua->is_type(-1, object_type_t::string))
	{
		lua->pop(3);
		return false;
	}

	info.ammo = lua->get_string(-1);
	lua->pop(2);

	lua->get_field(-1, xorstr("Penetration"));
	if (!lua->is_type(-1, object_type_t::boolean))
	{
		lua->pop(2);
		return false;
	}

	info.penetration = lua->get_bool(-1);
	lua->pop();

	lua->get_field(-1, xorstr("MaxRicochet"));
	if (!lua->is_type(-1, object_type_t::number))
	{
		lua->pop(2);
		return false;
	}

	info.max_ricochet = lua->get_number(-1);
	lua->pop();

	lua->get_field(-1, xorstr("RicochetCoin"));
	if (!lua->is_type(-1, object_type_t::number))
	{
		lua->pop(2);
		return false;
	}

	int ricochet_coin = lua->get_number(-1);
	lua->pop(2);

	info.max_penetration = 14;
	if (strstr(info.ammo, xorstr("SniperPenetratedRound")))
	{
		info.max_penetration = 20;
	}
	else if (strstr(info.ammo, xorstr("pistol")))
	{
		info.max_penetration = 9;
	}
	else if (strstr(info.ammo, xorstr("357")))
	{
		info.max_penetration = 12;
	}
	else if (strstr(info.ammo, xorstr("smg1")))
	{
		info.max_penetration = 14;
	}
	else if (strstr(info.ammo, xorstr("ar2")))
	{
		info.max_penetration = 16;
	}
	else if (strstr(info.ammo, xorstr("buckshot")))
	{
		info.max_penetration = 5;
	}
	else if (strstr(info.ammo, xorstr("slam")))
	{
		info.max_penetration = 5;
	}
	else if (strstr(info.ammo, xorstr("AirboatGun")))
	{
		info.max_penetration = 17;
	}

	info.ricochet = false;
	if (strstr(info.ammo, xorstr("pistol")) || strstr(info.ammo, xorstr("buckshot")) || strstr(info.ammo, xorstr("slam")) || strstr(info.ammo, xorstr("SniperPenetratedRound")))
	{
		info.ricochet = true;
	}
	else
	{
		/*
		if (ricochet_coin == 1)
		{
			info.ricochet = true;
		}
		else if (ricochet_coin >= 2)
		{
			info.ricochet = false;
		}
		*/
	}

	if (strstr(info.ammo, xorstr("SniperPenetratedRound")))
	{
		info.max_ricochet = 10;
	}
	else if (strstr(info.ammo, xorstr("pistol")))
	{
		info.max_ricochet = 2;
	}
	else if (strstr(info.ammo, xorstr("357")))
	{
		info.max_ricochet = 5;
	}
	else if (strstr(info.ammo, xorstr("smg1")))
	{
		info.max_ricochet = 4;
	}
	else if (strstr(info.ammo, xorstr("ar2")))
	{
		info.max_ricochet = 5;
	}
	else if (strstr(info.ammo, xorstr("buckshot")))
	{
		info.max_ricochet = 0;
	}
	else if (strstr(info.ammo, xorstr("slam")))
	{
		info.max_ricochet = 0;
	}
	else if (strstr(info.ammo, xorstr("AirboatGun")))
	{
		info.max_ricochet = 8;
	}

	return true;
}

bool lua_utilities::build_swb_info(c_base_combat_weapon* weapon, swb_info& info)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return false;

	if (!weapon->uses_lua())
		return false;

	weapon->push_entity();

	lua->get_field(-1, xorstr("PenStr"));
	if (!lua->is_type(-1, object_type_t::number))
	{
		lua->pop(2);
		return false;
	}

	info.pen_str = lua->get_number(-1);

	lua->pop();

	lua->get_field(-1, xorstr("PenMod"));
	if (!lua->is_type(-1, object_type_t::number))
	{
		lua->pop(2);
		return false;
	}

	info.pen_mod = lua->get_number(-1);

	lua->pop(2);

	return true;
}

const char* lua_utilities::language_get_phrase(const char* phrase)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_menu);
	if (!lua)
		return phrase;

	lua->push_special(lua_special_glob);
	lua->get_field(-1, xorstr("language"));
	if (!lua->is_type(-1, object_type_t::table))
	{
		lua->pop(2);
		return "";
	}

	lua->get_field(-1, xorstr("GetPhrase"));
	if (!lua->is_type(-1, object_type_t::function))
	{
		lua->pop(3);
		return "";
	}

	lua->push_string(phrase);
	lua->call(1, 1);

	const char* value = lua->get_string(-1);
	lua->pop(3);

	return value;
}

void lua_utilities::random_seed(float seed)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_menu);
	if (!lua)
		return;

	lua->push_special(lua_special_glob);
	lua->get_field(-1, xorstr("math"));
	if (!lua->is_type(-1, object_type_t::table))
	{
		lua->pop(2);
		return;
	}

	lua->get_field(-1, xorstr("randomseed"));
	if (!lua->is_type(-1, object_type_t::function))
	{
		lua->pop(3);
		return;
	}

	lua->push_number(seed);
	lua->call(1, 0);

	lua->pop(2);
}

float lua_utilities::rand(float min, float max)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_menu);
	if (!lua)
		return 0.f;

	lua->push_special(lua_special_glob);
	lua->get_field(-1, xorstr("math"));
	if (!lua->is_type(-1, object_type_t::table))
	{
		lua->pop(2);
		return 0.f;
	}

	lua->get_field(-1, xorstr("Rand"));
	if (!lua->is_type(-1, object_type_t::function))
	{
		lua->pop(3);
		return 0.f;
	}

	lua->push_number(min);
	lua->push_number(max);
	lua->call(2, 1);

	float value = lua->get_number(-1);
	lua->pop(3);

	return value;
}