void hooks::handles::paint_traverse(i_panel* panel, v_panel v_panel, bool force_repaint, bool allow_force)
{
	const char* name = interfaces::panel->get_name(v_panel);

	if (!globals::overlay_popup_panel)
	{
		if (strcmp(xorstr("OverlayPopupPanel"), name) == 0)
			globals::overlay_popup_panel = v_panel;
	}
	else if (globals::overlay_popup_panel == v_panel)
	{
		interfaces::panel->set_key_board_input_enabled(v_panel, settings::menu::opened);
		interfaces::panel->set_mouse_input_enabled(v_panel, settings::menu::opened);
	}

	if (!globals::mat_system_top_panel)
	{
		if (strcmp(xorstr("MatSystemTopPanel"), name) == 0)
			globals::mat_system_top_panel = v_panel;
	}
	else if (globals::mat_system_top_panel == v_panel)
	{
		if (interfaces::engine->is_in_game())
		{
			D3DMATRIX world_to_view, view_to_projection, world_to_pixels;
			interfaces::render_view->get_matrices_for_view(*interfaces::view_render->get_view_setup(), &world_to_view, &view_to_projection, &globals::world_to_screen, &world_to_pixels);
		}
	}

	originals::paint_traverse(panel, v_panel, force_repaint, allow_force);
}