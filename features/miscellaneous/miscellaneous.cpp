#include "miscellaneous.h"

void miscellaneous::run()
{
	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (!local_player || !local_player->is_alive())
		return;

	if (settings::aimbot::accuracy::disable_visual_recoil)
		local_player->get_punch_angle() = c_vector();
}

void miscellaneous::third_person(c_view_setup& view)
{
	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (!local_player)
		return;

	if (!settings::miscellaneous::globals::third_person::enable)
		return;

	if (!settings::miscellaneous::globals::third_person::hotkey.check())
		return;

	//https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/sp/src/game/client/in_camera.cpp#L59
	interfaces::input->camera_in_third_person = true;

	trace_t trace;
	c_trace_filter filter;
	filter.skip = local_player;

	c_vector dir;
	math::angle_to_vector(view.angles, dir);

	c_vector origin = view.origin + ((dir * -1) * settings::miscellaneous::globals::third_person::distance);

	ray_t ray(view.origin, origin);
	interfaces::engine_trace->trace_ray(ray, MASK_SOLID, &filter, &trace);

	view.origin = trace.end;
}