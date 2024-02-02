struct lua_user_data_t
{
    void*           data;
    unsigned char	type;
};

enum lua_special_t
{
    lua_special_glob,
    lua_special_env,
    lua_special_red,
};

enum lua_type_t
{
    lua_type_client,
    lua_type_server,
    lua_type_menu
};