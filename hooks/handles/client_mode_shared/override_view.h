bool __fastcall hooks::handles::override_view(i_client_mode* ecx, c_view_setup* view_setup)
{
    globals::fov = view_setup->fov;

    return originals::override_view(ecx, view_setup);
}