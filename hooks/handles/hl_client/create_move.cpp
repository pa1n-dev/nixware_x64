void __fastcall hooks::handles::hl_client_create_move(c_hl_client* client, int sequence_number, float input_sample_frametime, bool active)
{
	originals::hl_client_create_move(client, sequence_number, input_sample_frametime, active);
}