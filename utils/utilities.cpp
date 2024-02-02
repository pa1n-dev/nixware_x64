#include "utilities.h"

bool utilities::game_is_full_loaded()
{
	return GetModuleHandleA(xorstr("client.dll"))
		&& GetModuleHandleA(xorstr("engine.dll"))
		&& GetModuleHandleA(xorstr("menusystem.dll"))
		&& GetModuleHandleA(xorstr("gameoverlayrenderer64.dll"))
		&& GetModuleHandleA(xorstr("materialsystem.dll"))
		&& GetModuleHandleA(xorstr("lua_shared.dll"))
		&& GetModuleHandleA(xorstr("vgui2.dll"));
}

void utilities::attach_console()
{
	AllocConsole();
	freopen(xorstr("conin$"), "r", stdin);
	freopen(xorstr("conout$"), "w", stdout);
	freopen(xorstr("conout$"), "w", stderr);
	SetConsoleTitleA(xorstr("Nixware"));
}

q_angle utilities::calc_angle(const c_vector& from, const c_vector& to)
{
	q_angle ang;
	c_vector delta = from - to;

	ang.y = atanf(delta.y / delta.x) * 57.295779513082f;
	ang.x = atanf(-delta.z / delta.length2d()) * -57.295779513082f;

	if (delta.x >= 0.f)
		ang.y += 180.f;

	return ang;
}

float utilities::get_fov(const q_angle& from, const q_angle& to)
{
	c_vector delta = to - from;
	delta.normalize();
	return sqrtf(powf(delta.x, 2) + powf(delta.y, 2));
}

bool utilities::screen_transform(const c_vector& in, c_vector& out)
{
	auto exception_filter = [](int code, PEXCEPTION_POINTERS ex)
	{
		return EXCEPTION_EXECUTE_HANDLER;
	};

	__try
	{
		const D3DMATRIX& world_matrix = globals::world_to_screen;

		const auto w = world_matrix.m[3][0] * in.x + world_matrix.m[3][1] * in.y + world_matrix.m[3][2] * in.z + world_matrix.m[3][3];
		if (w < 0.001f)
		{
			out.x *= 100000;
			out.y *= 100000;
			return false;
		}

		out.x = world_matrix.m[0][0] * in.x + world_matrix.m[0][1] * in.y + world_matrix.m[0][2] * in.z + world_matrix.m[0][3];
		out.y = world_matrix.m[1][0] * in.x + world_matrix.m[1][1] * in.y + world_matrix.m[1][2] * in.z + world_matrix.m[1][3];
		out.z = 0.0f;

		out.x /= w;
		out.y /= w;

		return true;
	}
	__except (exception_filter(GetExceptionCode(), GetExceptionInformation()))
	{
		out.x *= 100000;
		out.y *= 100000;
		return false;
	}
}

bool utilities::world_to_screen(const c_vector& in, c_vector& out)
{
	if (!screen_transform(in, out))
		return false;

	int w, h;
	interfaces::engine->get_screen_size(w, h);

	out.x = (w / 2.0f) + (out.x * w) / 2.0f;
	out.y = (h / 2.0f) - (out.y * h) / 2.0f;

	return true;
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
		if (!world_to_screen(points[i], screen_points[i]))
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