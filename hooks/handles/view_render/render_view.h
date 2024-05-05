void __fastcall hooks::handles::render_view(i_view_render* view_render, c_view_setup& view, int flags, int to_draw)
{
	miscellaneous::third_person(view);

	globals::view_origin = view.origin;

	originals::render_view(view_render, view, flags, to_draw);
}