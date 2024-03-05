#include "hooks.h"

#include "../features/menu/menu.h"
#include "../features/visuals/visuals.h"
#include "../features/aimbot/aimbot.h"
#include "../features/aimbot/penetrate_walls.h"
#include "../features/aimbot/predict_spread.h"
#include "../features/aimbot/backtrack/history.h"
#include "../features/aimbot/backtrack/lag_compensation.h"
#include "../features/miscellaneous/movement.h"

#include "handles/wndproc.h"
#include "handles/d3d9/present.h"
#include "handles/d3d9/reset.h"
#include "handles/html_panel/load_url.h"
#include "handles/html_panel/paint.h"
#include "handles/net_channel/send_datagram.h"
#include "handles/panel/paint_traverse.h"
#include "handles/hl_client/create_move.h"
#include "handles/hl_client/write_user_cmd_delta_to_buffer.h"
#include "handles/hl_client/frame_stage_notify.h"
#include "handles/view_render/render_view.h"
#include "handles/model_render/draw_model_execute.h"

void hooks::initialize()
{
    if (!min_hook.create_hook((LPVOID)memory::pattern_scanner(xorstr("gameoverlayrenderer64.dll"), xorstr("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 81 EC ? ? ? ? 4C 8B A4 24 ? ? ? ?")), &handles::present, (LPVOID*)&handles::originals::present))
        throw;

    if (!min_hook.create_hook((LPVOID)memory::pattern_scanner(xorstr("gameoverlayrenderer64.dll"), xorstr("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 50 48 8B F2 48 8B F9 48 8B D1")), &handles::reset, (LPVOID*)&handles::originals::reset))
        throw;

    if (!min_hook.create_hook((LPVOID)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("menusystem.dll"), xorstr("E8 ? ? ? ? EB 17 48 8B 0D ? ? ? ?")), 1, 5), &handles::html_panel_load_url, (LPVOID*)&handles::originals::html_panel_load_url))
        throw;

    if (!min_hook.create_hook((LPVOID)memory::pattern_scanner(xorstr("menusystem.dll"), xorstr("40 57 48 83 EC 40 48 8B F9")), &handles::html_panel_paint, (LPVOID*)&handles::originals::html_panel_paint))
        throw;

    //if (!min_hook.create_hook((LPVOID)memory::pattern_scanner(xorstr("engine.dll"), xorstr("40 55 53 56 57 41 55 41 56 41 57 48 8D AC 24 ? ? ? ?")), &handles::send_datagram, (LPVOID*)&handles::originals::send_datagram))
    //    throw; 

	if (!min_hook.create_hook((LPVOID)memory::get_virtual((PVOID**)interfaces::panel, 41), &handles::paint_traverse, (LPVOID*)&handles::originals::paint_traverse))
		throw;

    if (!min_hook.create_hook((LPVOID)memory::get_virtual((PVOID**)interfaces::hl_client, 21), &handles::create_move, (LPVOID*)&handles::originals::create_move))
        throw;

    if (!min_hook.create_hook((LPVOID)memory::get_virtual((PVOID**)interfaces::hl_client, 23), &handles::write_user_cmd_delta_to_buffer, (LPVOID*)&handles::originals::write_user_cmd_delta_to_buffer))
        throw;

    if (!min_hook.create_hook((LPVOID)memory::get_virtual((PVOID**)interfaces::hl_client, 35), &handles::frame_stage_notify, (LPVOID*)&handles::originals::frame_stage_notify))
        throw;

    if (!min_hook.create_hook((LPVOID)memory::get_virtual((PVOID**)interfaces::view_render, 6), &handles::render_view, (LPVOID*)&handles::originals::render_view))
        throw;

    if (!min_hook.create_hook((LPVOID)memory::get_virtual((PVOID**)interfaces::model_render, 20), &handles::draw_model_execute, (LPVOID*)&handles::originals::draw_model_execute))
        throw;

    if (!min_hook.enable_hook())
        throw;
 
    handles::originals::wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(FindWindowW(L"Valve001", 0), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(handles::wndproc)));
}

void hooks::unhook()
{
    
}