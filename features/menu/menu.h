#pragma once
#include "../../hooks/hooks.h"

namespace menu
{
	static ImGuiColorEditFlags color_edit4_flags = ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaPreview;

	void render() noexcept;
}