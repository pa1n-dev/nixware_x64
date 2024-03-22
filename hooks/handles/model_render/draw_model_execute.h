void __fastcall hooks::handles::draw_model_execute(c_model_render* model_render, void* state, model_render_info_t& info, matrix3x4* bone_to_world)
{
    if (!info.entity_index || info.entity_index == 0)
        return originals::draw_model_execute(model_render, state, info, bone_to_world);

    if (interfaces::engine->get_local_player() == info.entity_index)
        return originals::draw_model_execute(model_render, state, info, bone_to_world);

	if (settings::aimbot::visuals::backtrack && settings::aimbot::accuracy::backtrack)
	{
        lag_record record;
        if (history::get_latest_record(info.entity_index, record))
            originals::draw_model_execute(model_render, state, info, record.bone_to_world.get());
	}

    originals::draw_model_execute(model_render, state, info, bone_to_world);
}