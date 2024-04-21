#include "lua_utilities.h"

const char* lua_utilities::get_name(c_base_entity* entity)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return "";

	entity->push_entity();
	lua->get_field(-1, xorstr("GetName"));
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

	const char* value = lua->get_string(-1);

	lua->pop(3);

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
	lua->get_field(-1, xorstr("GetName"));
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

const char* lua_utilities::language_get_phrase(const char* phrase)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return phrase;

	lua->push_special(lua_special_glob);
	lua->get_field(-1, xorstr("language"));
	lua->get_field(-1, xorstr("GetPhrase"));
	lua->push_string(phrase);
	lua->call(1, 1);

	const char* value = lua->get_string(-1);
	lua->pop(3);

	return value;
}

void lua_utilities::random_seed(float seed)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return;

	lua->push_special(lua_special_glob);
	lua->get_field(-1, xorstr("math"));
	lua->get_field(-1, xorstr("randomseed"));
	lua->push_number(seed);
	lua->call(1, 0);

	lua->pop(2);
}

float lua_utilities::rand(float min, float max)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return 0;

	lua->push_special(lua_special_glob);
	lua->get_field(-1, xorstr("math"));
	lua->get_field(-1, xorstr("Rand"));
	lua->push_number(min);
	lua->push_number(max);
	lua->call(2, 1);

	float value = (float)lua->get_number(-1);
	lua->pop(3);

	return value;
}