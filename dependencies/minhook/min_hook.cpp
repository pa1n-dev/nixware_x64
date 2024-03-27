#include "min_hook.h"

c_min_hook::c_min_hook()
{
	if (MH_Initialize() != MH_OK)
		throw;
}

c_min_hook::~c_min_hook()
{
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

bool c_min_hook::create_hook(LPVOID target, PVOID detour, LPVOID* original)
{
	return MH_CreateHook(target, detour, original) == MH_OK;
}

bool c_min_hook::enable_hook(PVOID hook)
{
	return MH_EnableHook(hook) == MH_OK;
}

bool c_min_hook::remove_all_hooks()
{
	return MH_DisableHook(MH_ALL_HOOKS) == MH_OK;
}