#pragma once
#include <windows.h>
#include <string>
#include <string_view>
#include <vector>
#include <stdexcept>

#undef interface

namespace memory
{
	typedef void* (*interface_type)(const char* name, int* return_code);

	template<typename T>
	T* capture_interface(const char* module_name, const char* interface_name)
	{
		HMODULE module_handle = GetModuleHandleA(module_name);
		if (!module_handle)
			throw;

		FARPROC proc_address = GetProcAddress(module_handle, "CreateInterface");
		if (!proc_address)
			throw;

		interface_type create_interface = reinterpret_cast<interface_type>(proc_address);
		if (!create_interface)
			throw;

		T* interface = static_cast<T*>(create_interface(interface_name, nullptr));
		if (!interface)
			throw;

		return interface;
	}

	constexpr uintptr_t relative_to_absolute(uintptr_t address, int offset, int instruction_size = 7)
	{
		auto instruction = address + offset;
		int relative_address = *(int*)(instruction);
		return address + instruction_size + relative_address;
	}

	template<typename T>
	T* get_vmt_from_instruction(uintptr_t address, size_t offset = 0)
	{
		uintptr_t step = 3;
		uintptr_t instruction = address + offset;

		uintptr_t real_address = relative_to_absolute(instruction, step);
		return *(T**)(real_address);
	}

	template<typename T>
	T call_v_function(void* pp_class, int idx)
	{
		uint64_t* vtable = *(uint64_t**)pp_class;
		uint64_t address = vtable[idx];

		T function = reinterpret_cast<T>(address);
		return function;
	}

	inline uintptr_t get_virtual(PVOID** c, int idx)
	{
		return (uintptr_t)(*c)[idx];
	}

	uint8_t* pattern_scanner(const std::string& module_name, const std::string& signature);
}