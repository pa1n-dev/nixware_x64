#pragma once
#include <string>
#include <iostream>
#include <list>
#include <deque>
#include <thread>
#include <algorithm>
#include <map>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#include "../dependencies/xorstr/xorstr.h"
#include "../dependencies/minhook/min_hook.h"
#include "../dependencies/memory/memory.h"

#include "../utils/utilities.h"
#include "../utils/lua_utilities.h"
#include "../utils/render_manager.h"

#include "../sdk/interfaces.h"

#include "../settings.h"

namespace hooks
{
	void initialize();
	void unhook();

	namespace handles
	{
		namespace originals
		{
			inline WNDPROC wndproc = nullptr;
			inline HRESULT(APIENTRY* reset) (IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
			inline HRESULT(APIENTRY* present) (IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
			inline void(__thiscall* html_panel_load_url)(void*, const char*);
			inline int(__thiscall* html_panel_paint)(void*);
			inline int(__thiscall* send_datagram)(c_net_channel*, void*);
			inline void(__fastcall* paint_traverse)(i_panel*, v_panel, bool, bool);
			inline void(__thiscall* create_move)(c_hl_client*, int, float, bool);
			inline bool(*write_user_cmd_delta_to_buffer)(c_hl_client*, void*, int, int, bool);
			inline void(__thiscall* frame_stage_notify)(c_hl_client*, ñlient_frame_stage_t);
			inline void(__thiscall* render_view)(i_view_render*, c_view_setup&, int, int);
			inline void(__thiscall* draw_model_execute)(c_model_render*, void*, model_render_info_t&, matrix3x4*);
		}

		LRESULT CALLBACK wndproc(HWND, UINT, WPARAM, LPARAM);
		HRESULT APIENTRY present(IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
		HRESULT APIENTRY reset(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
		void __fastcall html_panel_load_url(void*, const char*);
		int __fastcall html_panel_paint(void*);
		int __fastcall send_datagram(c_net_channel*, void*);
		void paint_traverse(i_panel*, v_panel, bool, bool);
		void __fastcall create_move(c_hl_client*, int, float, bool);
		bool write_user_cmd_delta_to_buffer(c_hl_client*, void*, int, int, bool);
		void __fastcall frame_stage_notify(c_hl_client*, ñlient_frame_stage_t);
		void __fastcall render_view(i_view_render*, c_view_setup&, int, int);
		void __fastcall draw_model_execute(c_model_render*, void*, model_render_info_t&, matrix3x4*);
	}
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);