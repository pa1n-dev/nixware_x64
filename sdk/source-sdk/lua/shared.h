class c_lua_shared
{
public:
    c_lua_interface* get_interface(lua_type_t state)
    {
        return memory::call_v_function<c_lua_interface* (__thiscall*)(void*, lua_type_t)>(this, 6)(this, state);
    }
};