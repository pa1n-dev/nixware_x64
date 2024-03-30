void __fastcall hooks::handles::frame_stage_notify(c_hl_client* client, ñlient_frame_stage_t stage)
{
	miscellaneous::disable_visual_recoil();

	originals::frame_stage_notify(client, stage);

	if (stage == frame_net_update_end)
		history::update();
}