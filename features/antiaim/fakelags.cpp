#include "fakelags.h"

bool fakelags::run(c_user_cmd* cmd)
{
	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (!local_player || !local_player->is_alive())
		return true;

	if (settings::antiaim::globals::fake_duck && cmd->buttons & IN_DUCK && local_player->get_flags() & FL_ONGROUND)
	{
		if (cmd->command_number & 1)
		{
			cmd->buttons &= ~IN_DUCK;
			return false;
		}

		return true;
	}

	if (!settings::antiaim::fakelags::enable || cmd->buttons & IN_ATTACK)
		return true;

	if (interfaces::client_state->choked_commands < settings::antiaim::fakelags::count)
	{
        switch (settings::antiaim::fakelags::method) 
        {
        case 0:
            if (local_player->get_flags() & FL_ONGROUND)
                return false;
            break;
		case 1:
			if (!(local_player->get_flags() & FL_ONGROUND))
				return false;
			break;
        case 2:
            if (local_player->get_velocity().length_2d() > 50.f)
                return false;
            break;
        case 3:
            if (local_player->get_velocity().length_2d() < 50.f)
                return false;
            break;
        case 4:
            return false;
        default:
            break;
        }
	}

	return true;
}

//https://www.unknowncheats.me/forum/garry-s-mod/615861-cusercmd-createmove-fakelag-x64.html
void fakelags::apply(bool send_packet)
{
	static void* p_send_packet = reinterpret_cast<void*>((uintptr_t)memory::pattern_scanner(xorstr("engine.dll"), xorstr("40 55 53 48 8D AC 24 38 F0 FF FF B8 C8 10 00 00 E8 ?? ?? ?? ?? 48 2B E0 0F 29 B4 24 B0 10 00 00")) + 0x168);

	static uint8_t jz_bytes[] = { 0x0f, 0x84, 0x04, 0x01, 0x00, 0x00 };
	static uint8_t jnz_bytes[] = { 0x0f, 0x85, 0x04, 0x01, 0x00, 0x00 };

	DWORD old_protect;
	VirtualProtect(p_send_packet, 6, PAGE_EXECUTE_READWRITE, &old_protect);
	memcpy(p_send_packet, send_packet ? jz_bytes : jnz_bytes, 6);
	VirtualProtect(p_send_packet, 6, old_protect, &old_protect);
}