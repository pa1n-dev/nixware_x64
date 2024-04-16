#include "lua.h"

void lua::run_string(const std::string& path)
{
	std::ifstream file(path);

	if (!file.is_open())
		return;

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string file_content = buffer.str();

	file.close();

	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return;

	lua->run_string("", "", file_content.c_str());
}

void lua::dumper(const std::string& filename, const std::string& string_to_run)
{
	if (!settings::lua::miscellaneous::dumper)
		return;

	c_net_channel* net_channel = interfaces::engine->get_net_channel();
	if (!net_channel)
		return;

	std::string address = net_channel->get_address();
	std::replace(address.begin(), address.end(), ':', '_');
	std::replace(address.begin(), address.end(), '.', '-');

	std::filesystem::path path = xorstr("C:/nixware/dumps/") + address + xorstr("/");
	path /= filename;

	std::filesystem::create_directories(path.parent_path());

	std::ofstream file(path);

	if (!file.is_open())
		return;

	file << string_to_run << std::endl;
	file.close();
}