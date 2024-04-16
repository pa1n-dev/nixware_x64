#pragma once

class i_prediction
{
public:
	void setup_move(c_base_entity* entity, c_user_cmd* cmd, i_move_helper* move_helper, c_move_data* move_data)
	{
		memory::call_v_function<void(__thiscall*)(void*, c_base_entity*, c_user_cmd*, i_move_helper*, c_move_data*)>(this, 18)(this, entity, cmd, move_helper, move_data);
	}

	void finish_move(c_base_entity* entity, c_user_cmd* cmd, c_move_data* move_data)
	{
		memory::call_v_function<void(__thiscall*)(void*, c_base_entity*, c_user_cmd*, void*)>(this, 19)(this, entity, cmd, move_data);
	}
};