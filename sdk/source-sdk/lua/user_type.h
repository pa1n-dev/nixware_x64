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

enum class object_type_t
{
    invalid = -1,
    nil,
    boolean,
    lightuserdata,
    number,
    string,
    table,
    function,
    userdata,
    thread,
    entity,
    vector,
    angle,
    physobj,
    save,
    restore,
    damageinfo,
    effectdata,
    movedata,
    recipientfilter,
    usercmd,
    scriptedvehicle,
    material,
    panel,
    particle,
    particleemitter,
    texture,
    usermsg,
    convar,
    imesh,
    matrix,
    sound,
    pixelvishandle,
    dlight,
    video,
    file,
    count
};