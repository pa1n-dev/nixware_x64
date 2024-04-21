#pragma once
#include <windows.h>
#include <string>
#include <string_view>
#include <vector>

namespace memory
{
	template<typename T>
	T* capture_interface(const char* module_name, const char* interface_name)
	{
		typedef void* (*interface_type)(const char* name, int* return_code);
		const auto temp = reinterpret_cast<interface_type>(GetProcAddress(GetModuleHandleA(module_name), "CreateInterface"));
		return static_cast<T*>(temp(interface_name, 0));
	}

	constexpr auto relative_to_absolute(uintptr_t address, int offset, int instruction_size = 6)
	{
		auto instruction = address + offset;

		int relative_address = *(int*)(instruction);
		auto real_address = address + instruction_size + relative_address;
		return real_address;
	}

	inline uintptr_t get_virtual(PVOID** c, int idx)
	{
		return (uintptr_t)(*c)[idx];
	}

	template<typename T>
	T* get_vmt_from_instruction(uintptr_t address)
	{
		uintptr_t step = 3;
		uintptr_t instruction_size = 7;
		uintptr_t instruction = address;

		uintptr_t relative_address = *(DWORD*)(instruction + step);
		uintptr_t real_address = instruction + instruction_size + relative_address;
		return *(T**)(real_address);
	}

	template<typename T>
	T* get_vmt_from_instruction(uintptr_t address, size_t offset)
	{
		uintptr_t step = 3;
		uintptr_t instruction_size = 7;
		uintptr_t instruction = address + offset;

		return *(T**)(relative_to_absolute(instruction, step, instruction_size));
	}

	template<typename T>
	T call_v_function(void* pp_class, int idx)
	{
		uint64_t* vtable = *(uint64_t**)pp_class;
		uint64_t address = vtable[idx];

		T function = reinterpret_cast<T>(address);
		return function;
	}

	uint8_t* pattern_scanner(const std::string& module_name, const std::string& signature);
}