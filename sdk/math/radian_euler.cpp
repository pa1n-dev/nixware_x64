#include "radian_euler.h"
#include <limits>

c_radian_euler::c_radian_euler()
{
	make_zero();
}

void c_radian_euler::make_inf()
{
	x = y = z = std::numeric_limits<float>::infinity();
}

void c_radian_euler::make_zero()
{
	x = y = z = 0.f;
}

float& c_radian_euler::operator[](int i)
{
	return ((float*)this)[i];
}

float c_radian_euler::operator[](int i) const
{
	return ((float*)this)[i];
}

bool c_radian_euler::operator==(const c_radian_euler& other) const
{
	return (other.x == x) && (other.y == y) && (other.z == z);
}

bool c_radian_euler::operator!=(const c_radian_euler& other) const
{
	return (other.x != x) || (other.y != y) || (other.z != z);
}