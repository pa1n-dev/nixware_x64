#pragma once

//https://media.discordapp.net/attachments/1194221664339234816/1211674968878747728/image.png?ex=65ef0f40&is=65dc9a40&hm=1fbef90240540692e40b12e5eb45d662fb482cfbadc59dea1c18da9685a8ba3a&=&format=webp&quality=lossless
class NET_SetConVar
{
public:
	NET_SetConVar(const char* name, const char* value)
	{
		using NET_SetConVar_t = NET_SetConVar* (__fastcall*)(void*, const char*, const char*);

		static NET_SetConVar_t NET_SetConVar;

		if (!NET_SetConVar)
			NET_SetConVar = (NET_SetConVar_t)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("engine.dll"), xorstr("E8 ? ? ? ? 45 33 C9 48 8D 54 24 ? 45 33 C0 48 8D 0D ? ? ? ?")), 1, 6);

		NET_SetConVar(this, name, value);
	}
};

class c_net_channel
{
public:
	char pad[8];
	int unk;
	int out_sequence_nr;
	int in_sequence_nr;
	int out_sequence_nr_ack;
	int out_reliable_state;
	int in_reliable_state;
	int choked_packets;

public:
	float get_latency(int flow)
	{
		return memory::call_v_function<float(__thiscall*)(void*, int)>(this, 9)(this, flow);
	}

	bool send_net_msg(NET_SetConVar& msg, bool force_reliable = false, bool voice = false)
	{
		return memory::call_v_function<bool(__thiscall*)(void*, NET_SetConVar&, bool, bool)>(this, 40)(this, msg, force_reliable, voice);
	}
};
