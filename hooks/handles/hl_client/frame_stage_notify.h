void __fastcall hooks::handles::frame_stage_notify(c_hl_client* client, ñlient_frame_stage_t stage)
{
	miscellaneous::run();

	originals::frame_stage_notify(client, stage);

	obs_bypass::frame_stage_notify(stage);

	if (stage == frame_net_update_end)
		history::update();
}