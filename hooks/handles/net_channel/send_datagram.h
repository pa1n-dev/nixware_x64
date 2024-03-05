int __fastcall hooks::handles::send_datagram(c_net_channel* net_channel, void* datagram)
{
	return originals::send_datagram(net_channel, datagram);
}