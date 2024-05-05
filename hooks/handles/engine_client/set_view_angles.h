void __fastcall hooks::handles::set_view_angles(c_engine_client* engine, q_angle& angle)
{
    static DWORD lua_set_view_angles = (DWORD)memory::pattern_scanner(xorstr("client.dll"), xorstr("C3 CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC 40 48 8B D1 0F 29 74 24 ?"));
    if (!lua_set_view_angles)
        throw;

    if (settings::aimbot::accuracy::disable_recoil && lua_set_view_angles - 0x7 == (DWORD)_ReturnAddress())
        return;

    originals::set_view_angles(engine, angle);
}