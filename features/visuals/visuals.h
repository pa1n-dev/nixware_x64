#pragma once

#include "../../dependencies/fonts/ubuntu_compressed.h"
#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_internal.h"
#include "../../dependencies/imgui/impl/imgui_impl_dx9.h"
#include "../../dependencies/imgui/impl/imgui_impl_win32.h"
#include "../../dependencies/imgui/freetype/imgui_freetype.h"

#include "../../sdk/interfaces.h"
#include "../../settings.h"

namespace visuals
{
	void render();
}