void __fastcall hooks::handles::create_move(c_hl_client* client, int sequence_number, float input_sample_frametime, bool active)
{
	originals::create_move(client, sequence_number, input_sample_frametime, active);

	c_user_cmd* cmd = interfaces::input->cmds + (sequence_number % MULTIPLAYER_BACKUP);
	if (!cmd)
		return;

	c_verified_user_cmd* verified_cmd = interfaces::input->verified_cmds + (sequence_number % MULTIPLAYER_BACKUP);
	if (!verified_cmd)
		return;

	movement::run(cmd);

	c_user_cmd old_cmd = *cmd;

	aimbot::run(cmd);
	predict_spread::run(cmd);

	bool send_packet = fakelags::run(cmd);
	antiaim::run(cmd, send_packet);
	animfix::run(cmd, send_packet);
	fakelags::apply(send_packet);

	movement::fix(cmd, old_cmd);

	verified_cmd->m_cmd = *cmd;
	verified_cmd->m_crc = cmd->get_checksum();

	lag_compensation::write_user_cmd_delta_to_buffer_callback();
}