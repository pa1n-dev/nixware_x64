#include "render_manager.h"

void render_manager::setup_imgui(IDirect3DDevice9* device)
{
	static std::once_flag once;
	std::call_once(once, [&]
	{
		CreateContext();
		ImGui_ImplWin32_Init(interfaces::window);
		ImGui_ImplWin32_GetDpiScaleForHwnd(interfaces::window);
		ImGui_ImplDX9_Init(device);

		draw_list = new ImDrawList(GetDrawListSharedData());
		draw_list_act = new ImDrawList(GetDrawListSharedData());
		draw_list_rendering = new ImDrawList(GetDrawListSharedData());

		StyleColorsDark();

		ImGuiIO& io = GetIO();

		//special thanks to nixer
		ImFontConfig cfg = {};

		cfg.PixelSnapH = true;
		cfg.OversampleH = cfg.OversampleV = 1;
		cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint;

		io.Fonts->AddFontFromFileTTF("C:/windows/fonts/verdana.ttf", 13.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
	});
}

void render_manager::shutdown()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	DestroyContext();
}

void render_manager::start_render()
{
	c_mat_render_context* ctx = interfaces::material_system->get_render_context();
	if (ctx)
	{
		ctx->begin_render();
		rt = ctx->get_render_target();
		ctx->set_render_target(nullptr);
		ctx->end_render();
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	NewFrame();
}

void render_manager::end_render()
{
	EndFrame();
	Render();

	if (render_manager::render_mutex.try_lock())
	{
		*render_manager::draw_list_rendering = *render_manager::draw_list_act;
		render_manager::render_mutex.unlock();
	}

	if (interfaces::engine->is_in_game())
	{
		//update imgui to latest ?
		ImDrawData draw_data;
		draw_data.Valid = true;
		draw_data.CmdLists = &draw_list;
		draw_data.CmdListsCount = 1;
		draw_data.TotalVtxCount = draw_list->VtxBuffer.size();
		draw_data.TotalIdxCount = draw_list->IdxBuffer.size();

		draw_data.DisplayPos = GetMainViewport()->Pos;
		draw_data.DisplaySize = GetMainViewport()->Size;
		draw_data.FramebufferScale = ImVec2(1.0f, 1.0f);

		ImGui_ImplDX9_RenderDrawData(&draw_data);
	}

	ImGui_ImplDX9_RenderDrawData(GetDrawData());

	if (rt)
	{
		c_mat_render_context* ctx = interfaces::material_system->get_render_context();
		if (ctx)
		{
			ctx->begin_render();
			ctx->set_render_target(rt);
			ctx->end_render();
		}
	}

	rt = nullptr;
}

void render_manager::setup_states(IDirect3DDevice9* device)
{
	device->CreateStateBlock(D3DSBT_ALL, &pixel_state);

	pixel_state->Capture();

	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_FOGENABLE, FALSE);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	device->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);

	device->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
}

void render_manager::backup_states(IDirect3DDevice9* device)
{
	pixel_state->Apply();
	pixel_state->Release();
}