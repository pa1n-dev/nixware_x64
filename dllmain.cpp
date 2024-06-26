#include "hooks/hooks.h"

BOOL WINAPI dll_detach()
{
    hooks::shutdown();
    render_manager::shutdown();

#ifdef _DEBUG
    utilities::detach_console();
#endif

    return TRUE;
}

DWORD WINAPI dll_entry(LPVOID thread_parameter)
{
    while (!utilities::game_is_full_loaded())
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

#ifdef _DEBUG
    utilities::attach_console();
#endif

    interfaces::initialize();
    hooks::initialize();

    while (!globals::unload)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    dll_detach();

    FreeLibraryAndExitThread(static_cast<HMODULE>(thread_parameter), EXIT_SUCCESS);
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(instance);

        HANDLE handle = CreateThread(nullptr, NULL, dll_entry, instance, NULL, nullptr);
        if (handle)
            CloseHandle(handle);

        break;
    }
    case DLL_PROCESS_DETACH:
    {
        if (reserved == nullptr)
            dll_detach();

        break;
    }
    }

    return TRUE;
}