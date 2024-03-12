#include "predict_spread.h"

void predict_spread::run(c_user_cmd* cmd)
{
	if (!settings::aimbot::accuracy::predict_spread)
		return;

	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (!local_player || !local_player->is_alive())
		return;

	c_base_combat_weapon* weapon = local_player->get_active_weapon();
	if (!weapon || !weapon->can_shoot())
		return;

	if (cmd->is_typing || cmd->is_world_clicking)
		return;

	if (!(cmd->buttons & IN_ATTACK))
		return;

	const char* weapon_base = lua_utilities::get_weapon_base(weapon);

	if (strstr(weapon_base, xorstr("bobs_")))
		return engine_spread(cmd, lua_utilities::get_weapon_spread(weapon));

	if (strstr(weapon_base, xorstr("swb_base")))
		return cone_spread(cmd, lua_utilities::get_weapon_cur_cone(weapon), cmd->command_number);
} 

void predict_spread::engine_spread(c_user_cmd* cmd, float spread_multiplier)
{
	if (spread_multiplier == 0.f)
		return;

	c_vector spread, dir, forward, right, up;
	q_angle out;

	int seed = md5_pseudo_random(cmd->command_number) & 0x7FFFFFFF;

	interfaces::random_stream->set_seed(seed & 255);
	float x = interfaces::random_stream->random_float(-0.5, 0.5) + interfaces::random_stream->random_float(-0.5, 0.5);
	float y = interfaces::random_stream->random_float(-0.5, 0.5) + interfaces::random_stream->random_float(-0.5, 0.5);

	spread.x = x * spread_multiplier;
	spread.y = y * spread_multiplier;
	spread.z = 0.0f;

	math::angle_to_vectors(cmd->view_angles, forward, right, up);

	dir = forward + (right * spread.x) + (up * spread.y);

	math::vector_to_angle(dir, out);
	out.normalize();
	out.clamp();

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

	out.normalize();
	out.clamp();

	cmd->view_angles -= out;
}