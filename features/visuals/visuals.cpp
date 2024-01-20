#include "visuals.h"
#include "../../utils/utilities.h"

void line(ImVec2 a, ImVec2 b, float color[4], float thickness)
{
	ImGui::GetWindowDrawList()->AddLine(a, b, ImGui::GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), thickness);
}

void render_box(box_t box, float color[4], float thickness)
{
	line(ImVec2(box.left, box.bottom), ImVec2(box.left, box.top), color, thickness);
	line(ImVec2(box.left, box.top), ImVec2(box.right, box.top), color, thickness);
	line(ImVec2(box.right, box.top), ImVec2(box.right, box.bottom), color, thickness);
	line(ImVec2(box.right, box.bottom), ImVec2(box.left, box.bottom), color, thickness);
}

void visuals::render()
{
	if (!interfaces::engine->is_in_game())
		return;

	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());

	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(io.DisplaySize);
	if (ImGui::Begin(xorstr("Visuals"), NULL, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground))
	{
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

				render_box(box, new float[4] { 1.f, 1.f, 1.f, 1.f }, 1.f);
			}
			else
			{
				if (!settings::visuals::entity::enable)
					continue;
			}
		}

		ImGui::End();
	}
}