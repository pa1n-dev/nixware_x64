void __fastcall hooks::handles::multiplayer_anim_state_update(void* anim_state, float yaw, float pitch)
{
    c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
    if (!local_player || !local_player->is_alive() || local_player->is_dormant())
        return originals::multiplayer_anim_state_update(anim_state, yaw, pitch);

    if (anim_state == local_player->get_anim_state() || anim_state == animfix::real_anim_state)
    {
        if (animfix::allow_anim_state_update)
        {
            animfix::allow_anim_state_update = false;
            return originals::multiplayer_anim_state_update(anim_state, yaw, pitch);
        }

        return;
    }

    return originals::multiplayer_anim_state_update(anim_state, yaw, pitch);
}
