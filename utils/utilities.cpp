#include "utilities.h"

bool utilities::game_is_full_loaded()
{
	return GetModuleHandleA(xorstr("client.dll"))
		&& GetModuleHandleA(xorstr("engine.dll"))
		&& GetModuleHandleA(xorstr("menusystem.dll"))
		&& GetModuleHandleA(xorstr("gameoverlayrenderer64.dll"))
		&& GetModuleHandleA(xorstr("materialsystem.dll"))
		&& GetModuleHandleA(xorstr("vgui2.dll"));
}

bool utilities::get_entity_box(c_base_entity* entity, box_t& box)
{
	c_vector pos = entity->get_render_origin();
	c_vector min = pos + entity->get_collidable()->mins();
	c_vector max = pos + entity->get_collidable()->maxs();

	c_vector points[] = { c_vector(min.x, min.y, min.z),
						c_vector(min.x, max.y, min.z),
						c_vector(max.x, max.y, min.z),
						c_vector(max.x, min.y, min.z),
						c_vector(max.x, max.y, max.z),
						c_vector(min.x, max.y, max.z),
						c_vector(min.x, min.y, max.z),
						c_vector(max.x, min.y, max.z) };

	c_vector screen_points[8];

	for (int i = 0; i < 8; ++i)
	{
		if (!math::world_to_screen(points[i], screen_points[i]))
			return false;
	}

	float left = screen_points[0].x;
	float top = screen_points[0].y;
	float right = screen_points[0].x;
	float bottom = screen_points[0].y;

	for (int i = 1; i < 8; ++i)
	{
		left = min(left, screen_points[i].x);
		top = max(top, screen_points[i].y);
		right = max(right, screen_points[i].x);
		bottom = min(bottom, screen_points[i].y);
	}

	if (isnan(left) || isnan(top) || isnan(right) || isnan(bottom))
		return false;

	box.left = left;
	box.top = top;
	box.right = right;
	box.bottom = bottom;

	return true;
}