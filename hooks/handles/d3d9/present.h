HRESULT APIENTRY hooks::handles::present(IDirect3DDevice9* device, CONST RECT* src, CONST RECT* dest, HWND wnd_override, CONST RGNDATA* dirty_region)
{
	using namespace ImGui;

	static std::once_flag once;
	std::call_once(once, [&]
	{
		HWND hwnd = FindWindowW(L"Valve001", 0);

		CreateContext();
		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplWin32_GetDpiScaleForHwnd(hwnd);
		ImGui_ImplDX9_Init(device);

		StyleColorsDark();

		ImGuiIO& io = GetIO();

		ImFontConfig config = ImFontConfig();
		config.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_MonoHinting;

		io.Fonts->AddFontFromMemoryCompressedTTF(ubuntu_compressed_data, ubuntu_compressed_size, 13, &config, io.Fonts->GetGlyphRangesCyrillic());
	});

	if (IsKeyPressed(ImGuiKey_Insert, false))
		settings::menu::opened = !settings::menu::opened;

	i_texture* rt = nullptr;
	c_mat_render_context* ctx = interfaces::material_system->get_render_context();
	if (ctx)
	{
		ctx->begin_render();
		rt = ctx->get_render_target();
		ctx->set_render_target(nullptr);
		ctx->end_render();
	}

	IDirect3DStateBlock9* pixel_state = nullptr;
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

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	NewFrame();

	menu::render();
	visuals::render();

	EndFrame();
	Render();

	ImGui_ImplDX9_RenderDrawData(GetDrawData());

	pixel_state->Apply();
	pixel_state->Release();

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

	return originals::present(device, src, dest, wnd_override, dirty_region);
}