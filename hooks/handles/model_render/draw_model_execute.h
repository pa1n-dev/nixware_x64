void __fastcall hooks::handles::draw_model_execute(c_model_render* model_render, void* state, model_render_info_t& info, matrix3x4* bone_to_world)
{
    if (!info.entity_index || info.entity_index == 0)
        return originals::draw_model_execute(model_render, state, info, bone_to_world);

	c_base_entity* entity = interfaces::entity_list->get_entity(info.entity_index);
	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());

	if (entity == local_player)
	{
		if (interfaces::input->camera_in_third_person)
		{
			if (animfix::created_real_matrix)
				originals::draw_model_execute(model_render, state, info, animfix::real_matrix);

			if (animfix::created_fake_matrix)
				originals::draw_model_execute(model_render, state, info, animfix::fake_matrix);

			return;
		}
	}

	if (settings::aimbot::visuals::backtrack && settings::aimbot::accuracy::backtrack)
	{
        lag_record record;
        if (history::get_latest_record(info.entity_index, record))
            originals::draw_model_execute(model_render, state, info, record.bone_to_world.get());
	}

    originals::draw_model_execute(model_render, state, info, bone_to_world);
}