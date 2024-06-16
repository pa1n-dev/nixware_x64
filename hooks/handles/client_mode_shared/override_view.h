bool __fastcall hooks::handles::override_view(c_client_mode_shared* client_mode_shared, c_view_setup* view)
{
    bool value = originals::override_view(client_mode_shared, view);

    if (settings::visuals::world::fov_changer::enable)
        view->fov = settings::visuals::world::fov_changer::value;

    globals::fov = view->fov;
    globals::view_angles = view->angles;

    return value;
}