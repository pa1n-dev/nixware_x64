void __fastcall hooks::handles::run_command(i_prediction* prediction, c_base_entity* player, c_user_cmd* cmd, void* move_helper)
{
    q_angle view;

    if (settings::aimbot::accuracy::disable_recoil)
        interfaces::engine->get_view_angles(view);

    originals::run_command(prediction, player, cmd, move_helper);

    if (settings::aimbot::accuracy::disable_recoil)
        interfaces::engine->set_view_angles(view);
}