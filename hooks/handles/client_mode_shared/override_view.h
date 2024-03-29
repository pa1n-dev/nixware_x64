bool __fastcall hooks::handles::override_view(i_client_mode_shared* client_mode_shared, c_view_setup* view)
{
    globals::fov = view->fov;
	
	miscellaneous::third_person(view);

    return originals::override_view(client_mode_shared, view);
}