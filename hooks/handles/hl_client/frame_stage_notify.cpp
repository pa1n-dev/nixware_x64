void __fastcall hooks::handles::frame_stage_notify(c_hl_client* client, int frame_stage)
{
	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (local_player && local_player->is_alive())
	{
		if (settings::aimbot::accuracy::disable_recoil)
			local_player->get_punch_angle() = q_angle(0, 0, 0);
	}

	return originals::frame_stage_notify(client, frame_stage);
}