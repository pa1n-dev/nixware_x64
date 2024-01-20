HRESULT APIENTRY hooks::handles::d3d9_reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	HRESULT result = originals::d3d9_reset(device, presentation_parameters);

	ImGui_ImplDX9_CreateDeviceObjects();

	return result;
}