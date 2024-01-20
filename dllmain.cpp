#include "utils/utilities.h"
#include "hooks/hooks.h"

void initialize()
{
    while (!utilities::game_is_full_loaded())
        std::this_thread::sleep_for(std::chrono::milliseconds(25));

    interfaces::initialize();
    hooks::initialize();
}

BOOL APIENTRY DllMain(HMODULE module, DWORD ul_reason_for_call, LPVOID reserved)
{
    DisableThreadLibraryCalls(module);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)initialize, module, 0, nullptr);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}