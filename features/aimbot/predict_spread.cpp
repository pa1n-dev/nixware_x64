#include "predict_spread.h"

void predict_spread::run(c_user_cmd* cmd)
{
	if (!settings::aimbot::accuracy::predict_spread)
		return;

	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (!local_player || !local_player->is_alive())
		return;

	c_base_combat_weapon* weapon = local_player->get_active_weapon();
	if (!weapon || !weapon->can_fire())
		return;

	if (cmd->is_typing || cmd->is_world_clicking)
		return;

	if (!(cmd->buttons & IN_ATTACK))
		return;

	const char* weapon_base = lua_utilities::get_weapon_base(weapon);

	if (strstr(weapon_base, xorstr("bobs_")))
		return engine_spread(cmd, lua_utilities::get_m9k_spread(cmd, weapon));

	if (strstr(weapon_base, xorstr("ptp_")))
		return engine_spread(cmd, lua_utilities::get_ptp_spread(weapon));

	if (strstr(weapon_base, xorstr("swb_")) || strstr(weapon_base, xorstr("cw_")))
	{
		cone_spread(cmd, lua_utilities::get_weapon_cur_cone(weapon), cmd->command_number);
		cmd->view_angles -= local_player->get_punch_angle();
	}

	if (strstr(weapon->get_print_name(), xorstr("#HL2_")) && !weapon->is_without_spread())
		return engine_spread(cmd, weapon->get_bullet_spread().x);
}

void predict_spread::engine_spread(c_user_cmd* cmd, float spread)
{
	if (spread == 0.f)
		return;

	c_vector dir, forward, right, up;
	q_angle out;

	int seed = md5_pseudo_random(cmd->command_number) & 0x7FFFFFFF;

	interfaces::random_stream->set_seed(seed & 255);
	float x = interfaces::random_stream->random_float(-0.5, 0.5) + interfaces::random_stream->random_float(-0.5, 0.5);
	float y = interfaces::random_stream->random_float(-0.5, 0.5) + interfaces::random_stream->random_float(-0.5, 0.5);

	math::angle_to_vectors(cmd->view_angles, forward, right, up);

	dir = forward + (right * (x * spread)) + (up * (y * spread));

	math::vector_to_angle(dir, out);

	cmd->view_angles += cmd->view_angles - out;
}

void predict_spread::cone_spread(c_user_cmd* cmd, float cone, float seed)
{
	if (cone == 0.f || seed == 0.f)
		return;

	lua_utilities::random_seed(seed);

	q_angle out;
	out.x = lua_utilities::rand(-cone, cone);
	out.y = lua_utilities::rand(-cone, cone);
	out.z = 0;
	out *= 25;

	cmd->view_angles -= out;
}