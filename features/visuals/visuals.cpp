#include "visuals.h"
#include "../aimbot/aimbot.h"

void visuals::render()
{
	if (!interfaces::engine->is_in_game())
		return;

	ImGuiIO& io = GetIO();
	SetNextWindowPos(ImVec2(0, 0));
	SetNextWindowSize(io.DisplaySize);

	if (!Begin(xorstr("Visuals"), NULL, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground))
		return;

	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());

	for (size_t i = 0; i < interfaces::entity_list->get_highest_entity_index(); i++)
	{
		c_base_entity* entity = interfaces::entity_list->get_entity(i);
		if (!entity)
			continue;

		if (entity->is_player())
		{
			if (!settings::visuals::players::enable)
				continue;

			if (!entity->is_alive())
				continue;

			if (!settings::visuals::players::dormant && entity->is_dormant())
				continue;

			if (entity == local_player)
				continue;

			box_t box{};
			if (!utilities::get_entity_box(entity, box))
				continue;

			if (settings::visuals::players::box)
				render_manager::box(box, settings::visuals::players::colors::box, 1.f);
		}
		else if (settings::visuals::entity::enable)
		{

		}
	}

	ImVec2 center(io.DisplaySize.x / 2, io.DisplaySize.y / 2);

	if (settings::aimbot::visuals::snaplines && aimbot::target.entity)
	{
		c_vector pos;
		if (utilities::world_to_screen(aimbot::target.shoot_pos, &pos))
			render_manager::line(center, ImVec2(pos.x, pos.y), settings::aimbot::visuals::colors::snaplines, 1.f);
	}

	if (settings::aimbot::visuals::fov)
	{
		float screen_fov = tanf(math::deg2rad(0.5f * globals::fov)) * ((io.DisplaySize.x / io.DisplaySize.y) / (4.f / 3.f));
		float radius = tanf(math::deg2rad(settings::aimbot::globals::fov * 0.5) * 2) / screen_fov * (io.DisplaySize.x * 0.5);

		render_manager::circle(center, radius, settings::aimbot::visuals::colors::fov, 100, 1.f);
	}

	End();
}