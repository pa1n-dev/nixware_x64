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