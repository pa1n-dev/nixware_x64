#include "lua.h"

void lua::executor()
{
	auto l = globals::waiting_to_be_executed.load();
	if (!l.first || !l.second)
		return;

	c_lua_interface* lua = interfaces::lua_shared->get_interface(lua_type_client);
	if (!lua)
		return;

	std::ifstream file(l.second);
	if (!file.is_open())
		return;

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	const char* data = buffer.str().c_str();
	lua->run_string("", "", data);

	globals::waiting_to_be_executed.store(std::make_pair(false, nullptr));
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

	std::regex forbidden(xorstr("[^a-zA-Z0-9_\\-]"));
	std::regex_replace(filename, forbidden, "");

	std::filesystem::path path = xorstr("C:/nixware/dumps/") + address + xorstr("/");
	path /= filename;

	if (!std::filesystem::exists(path.parent_path()) || !std::filesystem::is_directory(path.parent_path()))
		std::filesystem::create_directories(path.parent_path());

	std::ofstream file(path);

	if (!file.is_open())
		return;

	file << string_to_run << std::endl;
	file.close();
}