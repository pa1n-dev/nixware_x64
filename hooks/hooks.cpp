#include "hooks.h"

#include "../features/menu/menu.h"
#include "../features/visuals/visuals.h"

#include "../settings.h"

#include "../dependencies/fonts/ubuntu_compressed.h"
#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_internal.h"
#include "../dependencies/imgui/impl/imgui_impl_dx9.h"
#include "../dependencies/imgui/impl/imgui_impl_win32.h"
#include "../dependencies/imgui/freetype/imgui_freetype.h"

#include "handles/wnd_proc.cpp"
#include "handles/present.cpp"
#include "handles/reset.cpp"
#include "handles/html_panel/load_url.cpp"
#include "handles/html_panel/paint.cpp"
#include "handles/paint_traverse.cpp"

void hooks::initialize()
{
    if (MH_Initialize() != MH_OK)
        throw;

    if (MH_CreateHook((PVOID)memory::pattern_scanner(xorstr("gameoverlayrenderer64.dll"), xorstr("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 81 EC ? ? ? ? 4C 8B A4 24 ? ? ? ?")), &handles::d3d9_present, (LPVOID*)&handles::originals::d3d9_present) != MH_OK)
        throw;

    if (MH_CreateHook((PVOID)memory::pattern_scanner(xorstr("gameoverlayrenderer64.dll"), xorstr("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 50 48 8B F2 48 8B F9 48 8B D1")), &handles::d3d9_reset, (LPVOID*)&handles::originals::d3d9_reset) != MH_OK)
        throw;

    if (MH_CreateHook((PVOID)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("menusystem.dll"), xorstr("E8 ? ? ? ? EB 17 48 8B 0D ? ? ? ?")), 1, 5), &handles::html_panel_load_url, (LPVOID*)&handles::originals::html_panel_load_url) != MH_OK)
        throw;

    if (MH_CreateHook((PVOID)memory::pattern_scanner(xorstr("menusystem.dll"), xorstr("40 57 48 83 EC 40 48 8B F9")), &handles::html_panel_paint, (LPVOID*)&handles::originals::html_panel_paint) != MH_OK)
        throw;

	if (MH_CreateHook((PVOID)memory::get_virtual((PVOID**)interfaces::panel, 41), &handles::panel_paint_traverse, (LPVOID*)&handles::originals::panel_paint_traverse) != MH_OK)
		throw;

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
        throw;
}

void hooks::unhook()
{
    if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
        throw;
}