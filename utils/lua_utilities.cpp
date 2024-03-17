#include "lua_utilities.h"

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

const char* lua_utilities::get_weapon_base(c_base_combat_weapon* weapon)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return "";

	weapon->push_entity();

	lua->get_field(-1, xorstr("Base"));
	if (!lua->is_type(-1, 4))
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
	if (!lua->is_type(-1, 5))
	{
		lua->pop(2);
		return 0.f;
	}

	if (cmd->buttons & IN_ATTACK2)
	{
		lua->get_field(-1, xorstr("IronAccuracy"));
		if (!lua->is_type(-1, 3))
		{
			lua->pop(3);
			return 0.f;
		}
	}
	else
	{
		lua->get_field(-1, xorstr("Spread"));
		if (!lua->is_type(-1, 3))
		{
			lua->pop(3);
			return 0.f;
		}
	}

	double value = lua->get_number(-1);
	lua->pop(3);

	return value;
}

float lua_utilities::get_weapon_cur_cone(c_base_combat_weapon* weapon)
{
	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return 0.f;

	weapon->push_entity();

	lua->get_field(-1, xorstr("CurCone"));
	if (!lua->is_type(-1, 3))
	{
		lua->pop(2);
		return 0.f;
	}

	float value = lua->get_number(-1);

	lua->pop(2);

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