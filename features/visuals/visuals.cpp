#include "visuals.h"
#include "../aimbot/aimbot.h"

void visuals::render()
{
	if (!render_manager::draw_list)
		return;

	if (!interfaces::engine->is_in_game())
		return;

	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (!local_player)
		return;

	ImGuiIO& io = GetIO();

	render_manager::draw_list->_ResetForNewFrame();
	render_manager::draw_list->PushTextureID(io.Fonts->TexID);
	render_manager::draw_list->PushClipRectFullScreen();

	c_vector origin = local_player->get_abs_origin();

	for (size_t i = 0; i <= interfaces::entity_list->get_highest_entity_index(); i++)
	{
		c_base_entity* entity = interfaces::entity_list->get_entity(i);
		if (!entity)
			continue;

		if (entity->is_player())
		{
			if (!settings::visuals::esp::players::enable)
				continue;

			if (!entity->is_alive())
				continue;

			if (!settings::visuals::esp::players::dormant && entity->is_dormant())
				continue;

			if (entity == local_player)
				continue;

			box_t box;
			if (!utilities::get_entity_box(entity, box))
				continue;

			float offset = 0;
			float distance = origin.distance_to(entity->get_abs_origin());

			float alpha = std::clamp((settings::visuals::esp::players::render_distance - distance) / 100.f, 0.f, 1.f);
			if (alpha <= 0.0f)
				continue;

			PushStyleVar(ImGuiStyleVar_Alpha, alpha);

			if (settings::visuals::esp::players::box)
				render_manager::box(box, settings::visuals::esp::players::colors::box, 1.f);

			if (settings::visuals::esp::players::distance)
			{
				std::string distance_text = std::to_string((int)distance) + "m";
				render_manager::render_text(box, distance_text.c_str(), settings::visuals::esp::players::colors::distance, offset);
			}

			c_base_combat_weapon* weapon = entity->get_active_weapon();
			if (weapon)
			{
				if (settings::visuals::esp::players::weapon_name)
					render_manager::render_text(box, lua_utilities::language_get_phrase(lua_utilities::get_weapon_print_name(weapon)), settings::visuals::esp::players::colors::weapon_name, offset);
			}

			if (settings::visuals::esp::players::user_group)
				render_manager::render_text(box, lua_utilities::get_user_group(entity), settings::visuals::esp::players::colors::user_group, offset);

			if (settings::visuals::esp::players::rp_team)
				render_manager::render_text(box, lua_utilities::get_team_name(entity), settings::visuals::esp::players::colors::rp_team, offset);

			if (settings::visuals::esp::players::name)
				render_manager::render_text(box, lua_utilities::get_name(entity), settings::visuals::esp::players::colors::name, offset);

			PopStyleVar();
		}
		else if (settings::visuals::esp::entity::enable)
		{
			if (!settings::visuals::esp::entity::dormant && entity->is_dormant())
				continue;

			std::string name = entity->get_class_name();
			if (name.empty())
				continue;

			if (!settings::visuals::esp::entity::list.contains(name) || !settings::visuals::esp::entity::list[name].get<bool>())
				continue;

			box_t box;
			if (!utilities::get_entity_box(entity, box))
				continue;

			float offset = 0;
			float distance = origin.distance_to(entity->get_abs_origin());

			float alpha = std::clamp((settings::visuals::esp::entity::render_distance - distance) / 100.f, 0.f, 1.f);
			if (alpha <= 0.0f)
				continue;

			PushStyleVar(ImGuiStyleVar_Alpha, alpha);

			if (settings::visuals::esp::entity::box)
				render_manager::box(box, settings::visuals::esp::entity::colors::box, 1.f);

			if (settings::visuals::esp::entity::distance)
			{
				std::string distance_text = std::to_string((int)distance) + "m";
				render_manager::render_text(box, distance_text.c_str(), settings::visuals::esp::entity::colors::distance, offset);
			}

			if (settings::visuals::esp::entity::name)
				render_manager::render_text(box, name.c_str(), settings::visuals::esp::entity::colors::name, offset);

			PopStyleVar();
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

	render_manager::draw_list->PopClipRect();
}