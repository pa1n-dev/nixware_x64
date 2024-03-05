#pragma once

class c_multiplayer_anim_state
{
public:
	void update(float yaw, float pitch)
	{
		return memory::call_v_function<void(__thiscall*)(void*, float, float)>(this, 4)(this, yaw, pitch);
	}
};
