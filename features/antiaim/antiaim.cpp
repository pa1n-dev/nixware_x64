#include "antiaim.h"

void antiaim::run(c_user_cmd* cmd, bool send_packet)
{
    if (!settings::antiaim::globals::enable)
        return;

    if (!settings::antiaim::globals::hotkey.check())
        return;

    c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
    if (!local_player || !local_player->is_alive())
        return;

    if (local_player->get_move_type() == MOVETYPE_NOCLIP || local_player->get_move_type() == MOVETYPE_LADDER)
        return;

    if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK)
        return;

    q_angle view;
    interfaces::engine->get_view_angles(view);

    float pitch = 0.f;
    float yaw = 0.f;

    switch (settings::antiaim::globals::pitch)
    {
    case 0:
        pitch = 90.f;
        break;
    case 1:
        pitch = -90.f;
        break;
    }

    switch (settings::antiaim::globals::yaw)
    {
    case 0:
        yaw = view.y + (send_packet ^ settings::antiaim::globals::invert_yaw ? -90 : 90);
        break;
    case 1:
        yaw = local_player->get_anim_state()->current_feet_yaw + (send_packet ? 180 : 0);
        break;
    }

    cmd->view_angles.x = pitch;
    cmd->view_angles.y = yaw;
    cmd->view_angles.clamp();
}