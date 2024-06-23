void __fastcall hooks::handles::render_view(i_view_render* view_render, c_view_setup& view, int flags, int to_draw)
{
	if (settings::visuals::world::model_fov_changer::enable)
		view.fov_view_model = settings::visuals::world::model_fov_changer::value;

	miscellaneous::third_person(view);

	globals::view_origin = view.origin;

	originals::render_view(view_render, view, flags, to_draw);
	obs_bypass::render_view(view_render, view, flags, to_draw);
}