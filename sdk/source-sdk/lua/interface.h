class c_lua_interface;

struct lua_state_t
{
    char                pad_0000[120];
    c_lua_interface*    lua_lnterface;
};

typedef int(__cdecl* c_lua_function)(lua_state_t*);

class c_lua_interface
{
public:
    int top()
    {
        return memory::call_v_function<int(__thiscall*)(void*)>(this, 0)(this);
    }

    void push(int stack_pos)
    {
        return memory::call_v_function<void(__thiscall*)(void*, int)>(this, 1)(this, stack_pos);
    }

    void pop(int amount = 1)
    {
        return memory::call_v_function<void(__thiscall*)(void*, int)>(this, 2)(this, amount);
    }

    void get_table(int stack_pos)
    {
        return memory::call_v_function<void(__thiscall*)(void*, int)>(this, 3)(this, stack_pos);
    }

    void get_field(int stack_pos, const char* string_name)
    {
        return memory::call_v_function<void(__thiscall*)(void*, int, const char*)>(this, 4)(this, stack_pos, string_name);
    }

    void set_field(int stack_pos, const char* string_name)
    {
        return memory::call_v_function<void(__thiscall*)(void*, int, const char*)>(this, 5)(this, stack_pos, string_name);
    }

    void call(int args, int results)
    {
        return memory::call_v_function<void(__thiscall*)(void*, int, int)>(this, 10)(this, args, results);
    }

    int next(int stack_pos)
    {
        return memory::call_v_function<int(__thiscall*)(void*, int)>(this, 16)(this, stack_pos);
    }

    const char* get_string(int stack_pos = -1, unsigned int* out_length = nullptr)
    {
        return memory::call_v_function<const char* (__thiscall*)(void*, int, unsigned int*)>(this, 23)(this, stack_pos, out_length);
    }

    const double get_number(int stack_pos = -1)
    {
        return memory::call_v_function<double(__thiscall*)(void*, int)>(this, 24)(this, stack_pos);
    }

    bool get_bool(int stack_pos = -1)
    {
        return memory::call_v_function<bool(__thiscall*)(void*, int)>(this, 25)(this, stack_pos);
    }

    lua_user_data_t get_user_data(int stack_pos = -1)
    {
        return memory::call_v_function<lua_user_data_t (__thiscall*)(void*, int)>(this, 27)(this, stack_pos);
    }
    
    void push_nil()
    {
        return memory::call_v_function<void(__thiscall*)(void*)>(this, 28)(this);
    }

    void push_string(const char* value, unsigned int length = 0)
    {
        return memory::call_v_function<void(__thiscall*)(void*, const char*, unsigned int)>(this, 29)(this, value, length);
    }

    void push_number(double value)
    {
        return memory::call_v_function<void(__thiscall*)(void*, double)>(this, 30)(this, value);
    }

    void push_bool(bool value)
    {
        return memory::call_v_function<void(__thiscall*)(void*, bool)>(this, 31)(this, value);
    }

    void push_c_function(c_lua_function value)
    {
        return memory::call_v_function<void(__thiscall*)(void*, c_lua_function)>(this, 32)(this, value);
    }

    void push_special(lua_special_t type)
    {
        return memory::call_v_function<void(__thiscall*)(void*, lua_special_t)>(this, 38)(this, type);
    }

    bool is_type(int stack_pos, object_type_t type)
    {
        return memory::call_v_function<bool(__thiscall*)(void*, int, object_type_t)>(this, 39)(this, stack_pos, type);
    }

    int get_type(int stack_pos = -1)
    {
        return memory::call_v_function<int(__thiscall*)(void*, int)>(this, 40)(this, stack_pos);
    }

    const char* check_string(int stack_pos = -1)
    {
        return memory::call_v_function<const char* (__thiscall*)(void*, int)>(this, 43)(this, stack_pos);
    }

    double check_number(int stack_pos = -1)
    {
        return memory::call_v_function<double(__thiscall*)(void*, int)>(this, 44)(this, stack_pos);
    }

    const q_angle& get_angle(int stack_pos = -1)
    {
        return memory::call_v_function<const q_angle&(__thiscall*)(void*, int)>(this, 46)(this, stack_pos);
    }

    const c_vector& get_vector(int stack_pos = -1)
    {
        return memory::call_v_function<const c_vector&(__thiscall*)(void*, int)>(this, 47)(this, stack_pos);
    }

    void push_angle(const q_angle& value)
    {
        return memory::call_v_function<void(__thiscall*)(void*, const q_angle&)>(this, 48)(this, value);
    }

    void push_vector(const c_vector& value)
    {
        return memory::call_v_function<void(__thiscall*)(void*, const c_vector&)>(this, 49)(this, value);
    }

    bool is_user_data(int index)
    {
        return memory::call_v_function<bool(__thiscall*)(void*, int)>(this, 71)(this, index);
    }

    int get_flags(int index)
    {
        return memory::call_v_function<int(__thiscall*)(void*, int)>(this, 88)(this, index);
    }

    void run_string(char const* filename, char const* path, char const* string_to_run, bool run = true, bool show_errors = true)
    {
        return memory::call_v_function<void(__thiscall*)(c_lua_interface*, char const*, char const*, char const*, bool, bool)>(this, 92)(this, filename, path, string_to_run, run, show_errors);
    }
};