void hooks::handles::panel_paint_traverse(i_panel* rcx, v_panel panel, bool force_repaint, bool allow_force)
{
	originals::panel_paint_traverse(rcx, panel, force_repaint, allow_force);

	const char* name = interfaces::panel->get_name(panel);

	if (!globals::overlay_popup_panel)
	{
		if (strcmp(xorstr("OverlayPopupPanel"), name) == 0)
			globals::overlay_popup_panel = panel;
	}
	else if (globals::overlay_popup_panel == panel)
	{
		interfaces::panel->set_key_board_input_enabled(panel, settings::menu::opened);
		interfaces::panel->set_mouse_input_enabled(panel, settings::menu::opened);
	}

	if (!globals::mat_system_top_panel)
	{
		if (strcmp(xorstr("MatSystemTopPanel"), name) == 0)
			globals::mat_system_top_panel = panel;
	}
	else if (globals::mat_system_top_panel == panel)
	{
		if (interfaces::engine->is_in_game())
		{
			D3DMATRIX world_to_view, view_to_projection, world_to_pixels;
			interfaces::render_view->get_matrices_for_view(*interfaces::view_render->get_view_setup(), &world_to_view, &view_to_projection, &globals::world_to_screen, &world_to_pixels);
		}
	}
}