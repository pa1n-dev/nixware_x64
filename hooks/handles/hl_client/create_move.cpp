void __fastcall hooks::handles::hl_client_create_move(c_hl_client* client, int sequence_number, float input_sample_frametime, bool active)
{
	originals::hl_client_create_move(client, sequence_number, input_sample_frametime, active);

	c_user_cmd* cmd = interfaces::input->cmds + (sequence_number % 90);
	c_verified_user_cmd* verified_cmd = interfaces::input->verified_cmds + (sequence_number % 90);

	aimbot::run(cmd);

	verified_cmd->m_cmd = *cmd;
	verified_cmd->m_crc = cmd->get_checksum();
}