#include "engine_prediction.h"

void engine_prediction::start(c_user_cmd* cmd, c_base_entity* entity)
{
	c_base_entity* local_player = interfaces::entity_list->get_entity(interfaces::engine->get_local_player());
	if (!local_player || !local_player->is_alive())
		return;

	if (!entity)
		entity = local_player;

	if (!prediction_random_seed)
		prediction_random_seed = (unsigned int*)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("client.dll"), xorstr("48 8B D1 8B 0D ? ? ? ?")) + 0x3, 2, 6);

	player = entity;

	*prediction_random_seed = md5_pseudo_random(cmd->command_number) & 0x7FFFFFFF;

	old_curtime = interfaces::global_vars->curtime;
	old_frametime = interfaces::global_vars->frametime;

	interfaces::global_vars->curtime = player->get_tick_base() * interfaces::global_vars->interval_per_tick;
	interfaces::global_vars->frametime = interfaces::global_vars->interval_per_tick;

	interfaces::game_movement->start_track_prediction_errors(player);

	memset(&move_data, 0, sizeof(move_data));

	interfaces::prediction->setup_move(player, cmd, interfaces::move_helper, &move_data);
	interfaces::game_movement->process_movement(player, &move_data);
	interfaces::prediction->finish_move(player, cmd, &move_data);
}

void engine_prediction::end(c_user_cmd* cmd)
{
	if (!player || !player->is_alive())
		return;

	interfaces::game_movement->finish_track_prediction_errors(player);

	*prediction_random_seed = -1;

	interfaces::global_vars->curtime = old_curtime;
	interfaces::global_vars->frametime = old_frametime;

	player = nullptr;
}