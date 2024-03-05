LRESULT CALLBACK hooks::handles::wndproc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, w_param, l_param))
        return true;

    return CallWindowProcW(originals::wndproc, hwnd, msg, w_param, l_param);
}