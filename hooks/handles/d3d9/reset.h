HRESULT APIENTRY hooks::handles::reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	HRESULT result = originals::reset(device, presentation_parameters);

	ImGui_ImplDX9_CreateDeviceObjects();

	return result;
}