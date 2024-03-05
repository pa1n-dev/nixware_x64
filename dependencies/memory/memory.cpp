#include "memory.h"

uint8_t* memory::pattern_scanner(const std::string& module_name, const std::string& signature)
{
	auto* const module_handle = GetModuleHandleA(module_name.c_str());

	if (!module_handle)
		return nullptr;

	static auto pattern_to_byte = [](const std::string& pattern)
		{
			auto bytes = std::vector<int>();
			auto* const start = const_cast<char*>(pattern.c_str());
			auto* const end = const_cast<char*>(pattern.c_str()) + std::strlen(pattern.c_str());

			for (auto* current = start; current < end; ++current)
			{
				if (*current == '?')
				{
					++current;

					if (*current == '?')
						++current;

					bytes.push_back(-1);
				}
				else
					bytes.push_back(std::strtoul(current, &current, 16));
			}

			return bytes;
		};

	auto* const dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_handle);
	auto* const nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uint8_t*>(module_handle) + dos_header->e_lfanew);

	const auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
	auto pattern_bytes = pattern_to_byte(signature);
	auto* const scan_bytes = reinterpret_cast<uint8_t*>(module_handle);

	const auto s = pattern_bytes.size();
	auto* const d = pattern_bytes.data();

	for (auto i = 0ul; i < size_of_image - s; ++i)
	{
		bool found = true;

		for (auto j = 0ul; j < s; ++j)
		{
			if (scan_bytes[i + j] != d[j] && d[j] != -1)
			{
				found = false;
				break;
			}
		}

		if (found)
			return &scan_bytes[i];
	}

	return nullptr;
}