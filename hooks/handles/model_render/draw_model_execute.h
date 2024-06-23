void __fastcall hooks::handles::draw_model_execute(c_model_render* model_render, void* state, model_render_info_t& info, matrix3x4* bone_to_world)
{
	if (!obs_bypass::in_streamproof_view)
		return originals::draw_model_execute(model_render, state, info, bone_to_world);

	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (!local_player)
		return originals::draw_model_execute(model_render, state, info, bone_to_world);

	c_base_entity* entity = interfaces::entity_list->get_entity(info.entity_index);
	if (!entity)
		return originals::draw_model_execute(model_render, state, info, bone_to_world);

	if (entity == local_player)
	{
		if (interfaces::input->camera_in_third_person)
		{
			c_vector origin = local_player->get_abs_origin();

			if (animfix::created_real_matrix)
			{
				matrix3x4 matrix[MAX_STUDIO_BONES];
				for (int i = 0; i < MAX_STUDIO_BONES; i++)
				{
					std::copy(&animfix::real_matrix[i][0][0], &animfix::real_matrix[i][0][0] + 3 * 4, &matrix[i][0][0]);

					matrix[i][0][3] += origin.x;
					matrix[i][1][3] += origin.y;
					matrix[i][2][3] += origin.z;
				}

				hooks::handles::originals::draw_model_execute(model_render, state, info, matrix);
			}

			chams::push_material_override(settings::antihit::visuals::colors::fake_model, settings::antihit::visuals::fake_model::material_type);

			if (settings::antihit::visuals::fake_model::enable && animfix::created_fake_matrix)
				hooks::handles::originals::draw_model_execute(model_render, state, info, animfix::fake_matrix);

			chams::pop_material_override();

			return;
		}
	}
	else if (entity->is_player() && entity->is_alive())
	{
		if (settings::aimbot::visuals::backtrack::enable && settings::aimbot::accuracy::backtrack)
		{
			lag_record record;
			if (history::get_latest_record(info.entity_index, record))
			{
				chams::push_material_override(settings::aimbot::visuals::colors::backtrack, settings::aimbot::visuals::backtrack::material_type);
				hooks::handles::originals::draw_model_execute(model_render, state, info, record.bone_to_world.get());
				chams::pop_material_override();
			}
		}

		if (settings::visuals::chams::players::enable)
		{
			chams::push_ignore_z(settings::visuals::chams::players::ignore_walls);

			if (settings::visuals::chams::players::draw_original_model)
				hooks::handles::originals::draw_model_execute(model_render, state, info, bone_to_world);

			chams::push_material_override(settings::visuals::chams::colors::players, settings::visuals::chams::players::material_type);
			hooks::handles::originals::draw_model_execute(model_render, state, info, bone_to_world);
			chams::pop_material_override();

			chams::pop_ignore_z();

			return;
		}
	}
	else if (entity == interfaces::entity_list->get_entity_from_handle(local_player->get_hands()) || entity == interfaces::entity_list->get_entity_from_handle(local_player->get_view_model()))
	{
		if (settings::visuals::chams::hands::enable)
		{
			if (settings::visuals::chams::hands::draw_original_model)
				hooks::handles::originals::draw_model_execute(model_render, state, info, bone_to_world);

			chams::push_material_override(settings::visuals::chams::colors::hands, settings::visuals::chams::hands::material_type);
			hooks::handles::originals::draw_model_execute(model_render, state, info, bone_to_world);
			chams::pop_material_override();

			return;
		}
	}
	else
	{
		if (settings::visuals::chams::entity::enable)
		{
			std::string name = entity->get_class_name();

			if (!name.empty() && settings::visuals::chams::entity::list.contains(name) && settings::visuals::chams::entity::list[name].get<bool>())
			{
				chams::push_ignore_z(settings::visuals::chams::entity::ignore_walls);
				chams::push_material_override(settings::visuals::chams::colors::entity, settings::visuals::chams::entity::material_type);

				if (settings::visuals::chams::entity::draw_original_model)
					hooks::handles::originals::draw_model_execute(model_render, state, info, bone_to_world);

				hooks::handles::originals::draw_model_execute(model_render, state, info, bone_to_world);

				chams::pop_material_override();
				chams::pop_ignore_z();

				return;
			}
		}
	}

	originals::draw_model_execute(model_render, state, info, bone_to_world);
}