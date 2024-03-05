#pragma once

#include "../dependencies/fonts/ubuntu_compressed.h"
#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_internal.h"
#include "../dependencies/imgui/impl/imgui_impl_dx9.h"
#include "../dependencies/imgui/impl/imgui_impl_win32.h"
#include "../dependencies/imgui/freetype/imgui_freetype.h"

namespace render_manager
{
	using namespace ImGui;

	inline void line(ImVec2 a, ImVec2 b, float color[4], float thickness)
	{
		GetWindowDrawList()->AddLine(a, b, GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), thickness);
	}

	inline void line(float a, float b, float c, float d, float color[4], float thickness)
	{
		GetWindowDrawList()->AddLine(ImVec2(a, b), ImVec2(c, d), GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), thickness);
	}

	inline void text(ImVec2 from, const char* text, float color[4])
	{
		GetWindowDrawList()->AddText(from, GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), text);
	}

	inline void circle(ImVec2 position, float radius, float color[4], int num_segments, float thickness)
	{
		GetWindowDrawList()->AddCircle(position, radius, GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), num_segments, thickness);
	}

	inline void rect(ImVec2 from, ImVec2 to, float color[4], float rounding, ImDrawFlags flags, float thickness)
	{
		GetWindowDrawList()->AddRect(from, to, GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), rounding, flags, thickness);
	}

	inline void filled_rect(ImVec2 from, ImVec2 to, float color[4], float rounding, ImDrawFlags flags = 0)
	{
		GetWindowDrawList()->AddRectFilled(from, to, GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), rounding, flags);
	}

	inline void box(box_t box, float color[4], float thickness)
	{
		line(ImVec2(box.left, box.bottom), ImVec2(box.left, box.top), color, thickness);
		line(ImVec2(box.left, box.top), ImVec2(box.right, box.top), color, thickness);
		line(ImVec2(box.right, box.top), ImVec2(box.right, box.bottom), color, thickness);
		line(ImVec2(box.right, box.bottom), ImVec2(box.left, box.bottom), color, thickness);
	}
}