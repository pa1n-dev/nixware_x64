#include "quaternion.h"
#include <limits>

c_quaternion::c_quaternion()
{
	make_zero();
}

void c_quaternion::make_inf()
{
	x = y = z = w = std::numeric_limits<float>::infinity();
}

void c_quaternion::make_zero()
{
	x = y = z = w = 0.f;
}

float& c_quaternion::operator[](int i)
{
	return ((float*)this)[i];
}

float c_quaternion::operator[](int i) const
{
	return ((float*)this)[i];
}

bool c_quaternion::operator==(const c_quaternion& other) const
{
	return (other.x == x) && (other.y == y) && (other.z == z);
}

bool c_quaternion::operator!=(const c_quaternion& other) const
{
	return (other.x != x) || (other.y != y) || (other.z != z);
}