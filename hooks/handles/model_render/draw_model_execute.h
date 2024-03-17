void __fastcall hooks::handles::draw_model_execute(c_model_render* model_render, void* state, model_render_info_t& info, matrix3x4* bone_to_world)
{
    if (!info.entity_index || info.entity_index == 0)
        return originals::draw_model_execute(model_render, state, info, bone_to_world);

    if (interfaces::engine->get_local_player() == info.entity_index)
        return originals::draw_model_execute(model_render, state, info, bone_to_world);

	if (settings::aimbot::visuals::backtrack && settings::aimbot::accuracy::backtrack)
	{
        std::vector<lag_record> records;
        history::get_usable_records(info.entity_index, &records, settings::aimbot::accuracy::backtrack);

        if (!records.empty())
            originals::draw_model_execute(model_render, state, info, records.back().bone_to_world);
	}

    originals::draw_model_execute(model_render, state, info, bone_to_world);
}