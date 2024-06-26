#pragma once

#include "../sdk/interfaces.h"

namespace render_manager
{
	using namespace ImGui;

	inline ImDrawList* draw_list;

	static IDirect3DStateBlock9* pixel_state = nullptr;
	static i_texture* rt = nullptr;

	inline void line(ImVec2 a, ImVec2 b, float color[4], float thickness)
	{
		draw_list->AddLine(a, b, GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), thickness);
	}

	inline void line(float a, float b, float c, float d, float color[4], float thickness)
	{
		draw_list->AddLine(ImVec2(a, b), ImVec2(c, d), GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), thickness);
	}
	 
	inline void text(ImVec2 from, const char* text, float color[4])
	{
		draw_list->AddText(from, GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), text);
	}

	inline void circle(ImVec2 position, float radius, float color[4], int num_segments, float thickness)
	{
		draw_list->AddCircle(position, radius, GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), num_segments, thickness);
	}

	inline void rect(ImVec2 from, ImVec2 to, float color[4], float rounding, ImDrawFlags flags, float thickness)
	{
		draw_list->AddRect(from, to, GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), rounding, flags, thickness);
	}

	inline void filled_rect(ImVec2 from, ImVec2 to, float color[4], float rounding, ImDrawFlags flags = 0)
	{
		draw_list->AddRectFilled(from, to, GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), rounding, flags);
	}

	inline void box(box_t box, float color[4], float thickness)
	{
		draw_list->AddRect(ImVec2(box.left, box.top), ImVec2(box.right, box.bottom), GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), 0.f, 0, thickness);
	}

	inline void render_text(box_t box, const char* text, float color[4], float& text_offset)
	{
		if (!strcmp(text, ""))
			return; 

		ImVec2 size = CalcTextSize(text);
		draw_list->AddText(ImVec2((box.left + (box.right - box.left) / 2.f) - (size.x / 2.f), box.bottom - size.y - text_offset), GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), text);
		text_offset += size.y + 1;
	}

	void setup_imgui(IDirect3DDevice9* device);
	void shutdown();

	void start_render();
	void end_render();

	void setup_states(IDirect3DDevice9* device);
	void backup_states(IDirect3DDevice9* device);
}