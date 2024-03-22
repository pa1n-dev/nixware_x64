bool __fastcall hooks::handles::override_view(i_client_mode_shared* client_mode_shared, c_view_setup* view_setup)
{
    globals::fov = view_setup->fov;

	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (local_player && local_player->is_alive())
	{
		if (settings::aimbot::accuracy::disable_recoil)
			view_setup->angles -= local_player->get_punch_angle();
	}

    return originals::override_view(client_mode_shared, view_setup);
}