#pragma once

#include <iostream>
#include <d3dx9.h>

#include "../dependencies/memory/memory.h"
#include "../dependencies/xorstr/xorstr.h"

#include "math/vector.h"
#include "math/math.h"

#include "structs.h"
#include "source-sdk/c_engine_client.h"
#include "source-sdk/i_panel.h"
#include "source-sdk/c_view_setup.h"
#include "source-sdk/i_view_render.h"
#include "source-sdk/i_render_view.h"
#include "source-sdk/c_entity_list.h"
#include "source-sdk/c_texture.h"
#include "source-sdk/c_material_system.h"

namespace interfaces
{
	void initialize();

	inline c_engine_client*		engine;
	inline i_panel*				panel;
	inline i_view_render*		view_render;
	inline i_render_view*		render_view;
	inline c_entity_list*		entity_list;
	inline c_material_system*	material_system;
}