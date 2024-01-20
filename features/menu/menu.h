#pragma once

#include "../../dependencies/fonts/ubuntu_compressed.h"
#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_internal.h"
#include "../../dependencies/imgui/impl/imgui_impl_dx9.h"
#include "../../dependencies/imgui/impl/imgui_impl_win32.h"
#include "../../dependencies/imgui/freetype/imgui_freetype.h"

#include "../../dependencies/xorstr/xorstr.h"
#include "../../settings.h"

namespace menu
{
	static ImGuiColorEditFlags color_edit4_flags = ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaPreview;

	void render();
}