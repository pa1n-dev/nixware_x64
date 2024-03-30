void __fastcall hooks::handles::draw_model_execute(c_model_render* model_render, void* state, model_render_info_t& info, matrix3x4* bone_to_world)
{
	auto render_chams = [model_render, &state, &info](int material_type, float color[4], bool ignore_walls, matrix3x4* custom_bone_to_world)
	{
		static i_material* material = interfaces::material_system->find_material("models/debug/debugwhite", "Model textures");

		if (!material)
			return;

		material->increment_reference_count();

		bool backup_material_var_selfillum	= material->get_material_var_flag(material_var_selfillum);
		bool backup_material_var_wireframe	= material->get_material_var_flag(material_var_wireframe);
		bool backup_material_var_ignorez	= material->get_material_var_flag(material_var_ignorez);

		float backup_color[4];
		interfaces::render_view->get_color_modulation(backup_color);
		float backup_blend = interfaces::render_view->get_blend();

		switch (material_type)
		{
		case 1:
			material->set_material_var_flag(material_var_selfillum, true);
			break;
		case 2:
			material->set_material_var_flag(material_var_wireframe, true);
			break;
		}

		if (ignore_walls)
			material->set_material_var_flag(material_var_ignorez, false);

		interfaces::render_view->set_color_modulation(color);
		interfaces::render_view->set_blend(color[3]);
		interfaces::model_render->forced_material_override(material);

		originals::draw_model_execute(model_render, state, info, custom_bone_to_world);

		material->set_material_var_flag(material_var_selfillum, backup_material_var_selfillum);
		material->set_material_var_flag(material_var_wireframe, backup_material_var_wireframe);
		material->set_material_var_flag(material_var_ignorez, backup_material_var_ignorez);
		interfaces::render_view->set_color_modulation(backup_color);
		interfaces::render_view->set_blend(backup_blend);
		interfaces::model_render->forced_material_override(nullptr);
	};

	c_base_entity* entity = interfaces::entity_list->get_entity(info.entity_index);
	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());

	if (info.entity_index == interfaces::engine->get_local_player())
	{
		if (interfaces::input->cam_is_third_person())
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

				originals::draw_model_execute(model_render, state, info, matrix);
			}

			if (settings::antiaim::visuals::fake_model::enable && animfix::created_fake_matrix)
			{
				matrix3x4 matrix[MAX_STUDIO_BONES];
				for (int i = 0; i < MAX_STUDIO_BONES; i++)
				{
					std::copy(&animfix::fake_matrix[i][0][0], &animfix::fake_matrix[i][0][0] + 3 * 4, &matrix[i][0][0]);

					matrix[i][0][3] += origin.x;
					matrix[i][1][3] += origin.y;
					matrix[i][2][3] += origin.z;
				}

				render_chams(settings::antiaim::visuals::fake_model::material_type, settings::antiaim::visuals::colors::fake_model, false, matrix);
			}

			return;
		}
	}

	if (settings::aimbot::visuals::backtrack::enable && settings::aimbot::accuracy::backtrack)
	{
        lag_record record;
        if (history::get_latest_record(info.entity_index, record))
			render_chams(settings::aimbot::visuals::backtrack::material_type, settings::aimbot::visuals::colors::backtrack, false, record.bone_to_world.get());
	}

    originals::draw_model_execute(model_render, state, info, bone_to_world);
}