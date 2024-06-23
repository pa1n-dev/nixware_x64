#pragma once

#include <algorithm>
#include <cstdint>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <intrin.h>
#include <mutex>
#include <regex>
#include <format>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment(lib, "freetype.lib")

#include "../utils/hotkey.h"
#include "../dependencies/json/json.hpp"
#include "../dependencies/xorstr/xorstr.h"
#include "../dependencies/memory/memory.h"
#include "../dependencies/minhook/min_hook.h"
#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_internal.h"
#include "../dependencies/imgui/impl/imgui_impl_dx9.h"
#include "../dependencies/imgui/impl/imgui_impl_win32.h"
#include "../dependencies/imgui/freetype/imgui_freetype.h"

#include "source-sdk/math/vector.h"
#include "source-sdk/math/quaternion.h"
#include "source-sdk/math/radian_euler.h"
#include "source-sdk/math/math.h"

#include "source-sdk/definitions.h"
#include "source-sdk/lua/user_type.h"
#include "source-sdk/lua/interface.h"
#include "source-sdk/lua/shared.h"

#include "source-sdk/studio.h"
#include "source-sdk/c_studio_hdr.h"
#include "source-sdk/tier0/platform.h"
#include "source-sdk/tier1/str_tool.h"
#include "source-sdk/tier1/checksum_md5.h"
#include "source-sdk/tier1/c_utl_memory.h"
#include "source-sdk/tier1/c_utl_vector.h"
#include "source-sdk/tier1/key_values.h"
#include "source-sdk/engine/c_collideable.h"
#include "source-sdk/engine/c_render.h"
#include "source-sdk/anim_state/c_multiplayer_anim_state.h"
#include "source-sdk/anim_state/c_hl2mp_player_anim_state.h"
#include "source-sdk/entity/i_client_renderable.h"
#include "source-sdk/entity/i_client_networkable.h"
#include "source-sdk/entity/c_base_combat_weapon.h"
#include "source-sdk/entity/c_base_entity.h"
#include "source-sdk/vgui/i_panel.h"
#include "source-sdk/vgui/c_engine_vgui.h"
#include "source-sdk/client/c_view_setup.h"
#include "source-sdk/client/i_view_render.h"
#include "source-sdk/client/i_render_view.h"
#include "source-sdk/client/c_client_mode_shared.h"
#include "source-sdk/client/i_game_movement.h"
#include "source-sdk/server/c_entity_list.h"
#include "source-sdk/materialsystem/i_material.h"
#include "source-sdk/materialsystem/i_texture.h"
#include "source-sdk/materialsystem/c_material_system.h"
#include "source-sdk/engine/c_model_info.h"
#include "source-sdk/engine/c_model_render.h"
#include "source-sdk/engine/c_net_channel.h"
#include "source-sdk/engine/i_engine_trace.h"
#include "source-sdk/shared/c_user_cmd.h"
#include "source-sdk/shared/i_move_helper.h"
#include "source-sdk/client/c_input.h"
#include "source-sdk/client/c_hl_client.h"
#include "source-sdk/vstdlib/c_uniform_random_stream.h"
#include "source-sdk/vstdlib/c_cvar.h"
#include "source-sdk/vphysics/i_physics_surface_props.h"
#include "source-sdk/c_global_vars.h"
#include "source-sdk/c_engine_client.h"
#include "source-sdk/c_client_state.h"
#include "source-sdk/i_prediction.h"

#include "../utils/utilities.h"
#include "../utils/lua_utilities.h"
#include "../utils/render_manager.h"
#include "../utils/config_manager.h"
#include "../settings.h"

namespace interfaces
{
	void initialize();

	inline c_engine_client*			engine;
	inline i_panel*					panel;
	inline i_render_view*			render_view;
	inline c_entity_list*			entity_list;
	inline c_material_system*		material_system;
	inline c_hl_client*				hl_client;
	inline c_engine_vgui*			engine_vgui;
	inline c_model_info*			model_info;
	inline i_engine_trace*			engine_trace;
	inline c_lua_shared*			lua_shared;
	inline c_cvar*					cvar;
	inline c_model_render*			model_render;
	inline i_prediction*			prediction;
	inline i_game_movement*			game_movement;
	inline i_move_helper*			move_helper;
	inline i_physics_surface_props* physics_surface_props;
	inline i_view_render*			view_render;
	inline c_input*					input;
	inline c_render*				render;
	inline c_global_vars*			global_vars;
	inline c_client_state*			client_state;
	inline c_uniform_random_stream* random_stream;
	inline c_client_mode_shared*	client_mode_shared;
	inline HWND						window;
}