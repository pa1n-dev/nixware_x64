LRESULT APIENTRY hooks::handles::wnd_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	ImGui_ImplWin32_WndProcHandler(hwnd, msg, w_param, l_param);
	return CallWindowProcA(originals::wnd_proc, hwnd, msg, w_param, l_param);
}