#pragma once
#include <string>
#include <iostream>
#include <mutex>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#include "../dependencies/xorstr/xorstr.h"
#include "../dependencies/minhook/minhook.h"
#include "../dependencies/memory/memory.h"

#include "../utils/utilities.h"
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
			inline HRESULT(APIENTRY* d3d9_reset) (IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
			inline HRESULT(APIENTRY* d3d9_present) (IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
			inline void(__thiscall* html_panel_load_url)(void*, const char*);
			inline int(__thiscall* html_panel_paint)(void*);
			inline void(__fastcall* panel_paint_traverse)(i_panel*, v_panel, bool, bool);
			inline void(__thiscall* hl_client_create_move)(c_hl_client*, int, float, bool);
		}

		LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
		HRESULT APIENTRY d3d9_present(IDirect3DDevice9* device, CONST RECT* src, CONST RECT* dest, HWND wnd_override, CONST RGNDATA* dirty_region);
		HRESULT APIENTRY d3d9_reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters);
		void __fastcall html_panel_load_url(void* rcx, const char* url);
		int __fastcall html_panel_paint(void* rcx);
		void panel_paint_traverse(i_panel* self, v_panel panel, bool force_repaint, bool allow_force);
		void __fastcall hl_client_create_move(c_hl_client* hl_client, int sequence_number, float input_sample_frametime, bool active);
	}
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);