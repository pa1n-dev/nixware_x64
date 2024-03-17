bool __fastcall hooks::handles::override_view(i_client_mode_shared* client_mode_shared, c_view_setup* view_setup)
{
    globals::fov = view_setup->fov;

    return originals::override_view(client_mode_shared, view_setup);
}