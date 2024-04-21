bool __fastcall hooks::handles::override_view(c_client_mode_shared* client_mode_shared, c_view_setup* view)
{
    globals::fov = view->fov;
	
    return originals::override_view(client_mode_shared, view);
}