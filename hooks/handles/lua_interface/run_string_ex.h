int __fastcall hooks::handles::run_string_ex(c_lua_interface* lua, const char* filename, const char* path, const char* string_to_run, bool run, bool show_errors, bool dont_push_errors, bool no_returns)
{
    lua::dumper(filename, string_to_run);

    return originals::run_string_ex(lua, filename, path, string_to_run, run, show_errors, dont_push_errors, no_returns);
}