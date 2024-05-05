HRESULT APIENTRY hooks::handles::present(IDirect3DDevice9* device, CONST RECT* src, CONST RECT* dest, HWND wnd_override, CONST RGNDATA* dirty_region)
{
	render_manager::setup_imgui(device);
	render_manager::setup_states(device);
	render_manager::start_render();
	menu::render();
	render_manager::end_render();
	render_manager::backup_states(device);

	if (ImGui::IsKeyPressed(ImGuiKey_Insert, false))
		settings::menu::opened = !settings::menu::opened;

	return originals::present(device, src, dest, wnd_override, dirty_region);
}