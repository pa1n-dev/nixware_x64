#pragma once
#include "../sdk/interfaces.h"

#include "../utils/utilities.h"
#include "../utils/lua_utilities.h"
#include "../utils/render_manager.h"
#include "../settings.h"

#include "../features/menu/menu.h"
#include "../features/visuals/visuals.h"
#include "../features/visuals/obs_bypass.h"
#include "../features/visuals/chams.h"
#include "../features/aimbot/aimbot.h"
#include "../features/aimbot/penetrate_walls.h"
#include "../features/aimbot/predict_spread.h"
#include "../features/aimbot/engine_prediction.h"
#include "../features/aimbot/backtrack/history.h"
#include "../features/aimbot/backtrack/lag_compensation.h"
#include "../features/antiaim/antiaim.h"
#include "../features/antiaim/fakelags.h"
#include "../features/antiaim/animfix.h"
#include "../features/miscellaneous/miscellaneous.h"
#include "../features/miscellaneous/movement.h"
#include "../features/lua/lua.h"

namespace hooks
{
	void initialize();
	void shutdown();

	namespace handles
	{
		LRESULT CALLBACK	wndproc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
		HRESULT APIENTRY	present(IDirect3DDevice9* device, CONST RECT* src, CONST RECT* dest, HWND wnd_override, CONST RGNDATA* dirty_region);
		HRESULT APIENTRY	reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters);
		void __fastcall		html_panel_load_url(void* html_panel, const char* url);
		int __fastcall		html_panel_paint(void* html_panel);
		bool __fastcall		override_view(c_client_mode_shared* client_mode_shared, c_view_setup* view);
		int __fastcall		send_datagram(c_net_channel* net_channel, void* datagram);
		bool __fastcall     send_net_msg(c_net_channel* net_channel, i_net_message& msg, bool force_reliable, bool voice);
		void				paint_traverse(i_panel* panel, v_panel v_panel, bool force_repaint, bool allow_force);
		void __fastcall		create_move(c_hl_client* client, int sequence_number, float input_sample_frametime, bool active);
		bool				write_user_cmd_delta_to_buffer(c_hl_client* client, void* buf, int from, int to, bool is_new_command);
		void __fastcall		frame_stage_notify(c_hl_client* client, �lient_frame_stage_t stage);
		void __fastcall		render_view(i_view_render* view_render, c_view_setup& view, int flags, int to_draw);
		void __fastcall		draw_model_execute(c_model_render* model_render, void* state, model_render_info_t& info, matrix3x4* bone_to_world);
		void __fastcall		run_command(i_prediction* prediction, c_base_entity* player, c_user_cmd* cmd, void* move_helper);
		void __fastcall		multiplayer_anim_state_update(void* anim_state, float yaw, float pitch);
		int __fastcall		run_string_ex(c_lua_interface* lua, const char* filename, const char* path, const char* string_to_run, bool run, bool show_errors, bool dont_push_errors, bool no_returns);
		void __fastcall		set_view_angles(c_engine_client* engine, q_angle& angle);

		namespace originals
		{
			inline WNDPROC wndproc = nullptr;
			inline HRESULT(APIENTRY* reset) (IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
			inline HRESULT(APIENTRY* present) (IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
			inline void(__thiscall* html_panel_load_url)(void*, const char*);
			inline int(__thiscall* html_panel_paint)(void*);
			inline bool(__thiscall* override_view)(c_client_mode_shared*, c_view_setup*);
			inline int(__thiscall* send_datagram)(c_net_channel*, void*);
			inline bool(__thiscall* send_net_msg)(c_net_channel*, i_net_message&, bool, bool);
			inline void(__fastcall* paint_traverse)(i_panel*, v_panel, bool, bool);
			inline void(__thiscall* create_move)(c_hl_client*, int, float, bool);
			inline bool(*write_user_cmd_delta_to_buffer)(c_hl_client*, void*, int, int, bool);
			inline void(__thiscall* frame_stage_notify)(c_hl_client*, �lient_frame_stage_t);
			inline void(__thiscall* render_view)(i_view_render*, c_view_setup&, int, int);
			inline void(__thiscall* draw_model_execute)(c_model_render*, void*, model_render_info_t&, matrix3x4*);
			inline void(__fastcall* run_command) (i_prediction*, c_base_entity*, c_user_cmd*, void*);
			inline void(__thiscall* multiplayer_anim_state_update)(void*, float, float);
			inline int(__thiscall* run_string_ex)(c_lua_interface*, const char*, const char*, const char*, bool, bool, bool, bool);
			inline void(__thiscall* set_view_angles)(c_engine_client*, q_angle&);
		}
	}
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);