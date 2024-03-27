#pragma once
#include <exception>

#include "minhook/minhook.h"

inline class c_min_hook
{
public:
	c_min_hook();
	~c_min_hook();

	bool create_hook(LPVOID target, PVOID detour, LPVOID* original);
	bool enable_hook(PVOID hook = MH_ALL_HOOKS);
	bool remove_all_hooks();
} min_hook;