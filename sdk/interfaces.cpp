#include "interfaces.h"

void interfaces::initialize()
{
	engine = memory::capture_interface<c_engine_client>(xorstr("engine.dll"), xorstr("VEngineClient015"));
	if (!engine)
		throw;

	panel = memory::capture_interface<i_panel>(xorstr("vgui2.dll"), xorstr("VGUI_Panel009"));
	if (!panel)
		throw;

	render_view = memory::capture_interface<i_render_view>(xorstr("engine.dll"), xorstr("VEngineRenderView014"));
	if (!render_view)
		throw;

	entity_list = memory::capture_interface<c_entity_list>(xorstr("client.dll"), xorstr("VClientEntityList003"));
	if (!entity_list)
		throw;

	material_system = memory::capture_interface<c_material_system>(xorstr("materialsystem.dll"), xorstr("VMaterialSystem080"));
	if (!material_system)
		throw;

	hl_client = memory::capture_interface<c_hl_client>(xorstr("client.dll"), xorstr("VClient017"));
	if (!hl_client)
		throw;

	engine_vgui = memory::capture_interface<c_engine_vgui>(xorstr("engine.dll"), xorstr("VEngineVGui001"));
	if (!engine_vgui)
		throw;

	model_info = memory::capture_interface<c_model_info>(xorstr("engine.dll"), xorstr("VModelInfoClient006"));
	if (!model_info)
		throw;

	engine_trace = memory::capture_interface<i_engine_trace>(xorstr("engine.dll"), xorstr("EngineTraceClient003"));
	if (!engine_trace)
		throw;

	lua_shared = memory::capture_interface<c_lua_shared>(xorstr("lua_shared.dll"), xorstr("LUASHARED003"));
	if (!lua_shared)
		throw;

	view_render = memory::get_vmt_from_instruction<i_view_render>((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("48 8B 0D ? ? ? ? 48 8B 01 FF 50 18 48 8B 0D ? ? ? ? E8 ? ? ? ?")));
	if (!view_render)
		throw;

	input = memory::get_vmt_from_instruction<c_input>((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("48 8B 0D ? ? ? ? 48 8B 01 48 FF A0 90 00 00 00 CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 8B 0D ? ? ? ?")));
	if (!input)
		throw;

	render = memory::get_vmt_from_instruction<c_render>((uintptr_t)memory::pattern_scanner(xorstr("engine.dll"), xorstr("48 8B 0D ? ? ? ? 48 8B 01 48 FF 60 60 CC CC 48 8D 05 ? ? ? ?")));
	if (!render)
		throw;

	global_vars = *(c_global_vars**)memory::relative_to_absolute((uintptr_t)(memory::pattern_scanner(xorstr("client.dll"), xorstr("48 8B 05 ? ? ? ? 83 78 14 01 75 09"))), 0x3, 7);
	if (!global_vars)
		throw;

	random_stream = memory::get_vmt_from_instruction<c_uniform_random_stream>((uintptr_t)GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed"), 0x2);
	if (!random_stream)
		throw;
}