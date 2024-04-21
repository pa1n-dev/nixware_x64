bool __fastcall hooks::handles::send_net_msg(c_net_channel* net_channel, i_net_message& msg, bool force_reliable, bool voice)
{
    if (msg.get_group() == 8) //svc_VoiceData: 8
        voice = true;

    return originals::send_net_msg(net_channel, msg, force_reliable, voice);
}