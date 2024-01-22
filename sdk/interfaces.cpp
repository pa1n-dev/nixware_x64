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

	view_render = memory::get_vmt_from_instruction<i_view_render>((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("48 8B 0D ? ? ? ? 48 8B 01 FF 50 18 48 8B 0D ? ? ? ? E8 ? ? ? ?")));
	if (!view_render)
		throw;

	entity_list = memory::capture_interface<c_entity_list>(xorstr("client.dll"), xorstr("VClientEntityList003"));
	if (!entity_list)
		throw;

	material_system = memory::capture_interface<c_material_system>(xorstr("materialsystem.dll"), xorstr("VMaterialSystem080"));
	if (!material_system)
		throw;
}