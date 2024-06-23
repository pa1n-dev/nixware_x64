#pragma once

namespace key_values
{
    inline void* key_values()
    {
        using key_values_fn = void* (__fastcall*)(unsigned int);

        static key_values_fn key_values = (key_values_fn)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("E8 ? ? ? ? 4C 63 F7")), 1, 6);
        if (!key_values)
            throw;

        return key_values(0x48);
    }

    inline void* initialize(void* kv, const char* name)
    {
        using init_fn = void* (__fastcall*)(void*, const char*);

        static init_fn initialize = (init_fn)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("E8 ? ? ? ? 48 89 45 1F")), 1, 6);
        if (!initialize)
            throw;

        return initialize(kv, name);
    }

    inline bool load_from_buffer(void* kv, char const* resource_name, const char* buffer, void* file_system = NULL, const char* path_id = NULL)
    {
        using load_from_buffer_fn = bool(__fastcall*)(void*, char const*, const char*, void*, const char*, void*);

        static load_from_buffer_fn load_from_buffer = (load_from_buffer_fn)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("E8 ? ? ? ? 0F B6 D8 FF 15 ? ? ? ?")), 1, 6);
        if (!load_from_buffer)
            throw;

        return load_from_buffer(kv, resource_name, buffer, file_system, path_id, 0);
    }
}