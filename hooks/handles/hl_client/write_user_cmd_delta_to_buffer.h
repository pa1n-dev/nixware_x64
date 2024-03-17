bool hooks::handles::write_user_cmd_delta_to_buffer(c_hl_client* client, void* buf, int from, int to, bool is_new_command)
{
    return originals::write_user_cmd_delta_to_buffer(client, buf, from, to, is_new_command);
}