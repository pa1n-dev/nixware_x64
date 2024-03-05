#include "vector.h"
#include <limits>
#include <cmath>
#include <limits>
#include <algorithm>

c_vector::c_vector()
{
	make_zero();
}

c_vector::c_vector(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{

}

void c_vector::make_inf()
{
	x = y = z = std::numeric_limits<float>::infinity();
}

void c_vector::make_zero()
{
	x = y = z = 0.f;
}

void c_vector::normalize()
{
	while (x > 89.0f)
		x -= 180.0f;
	while (x < -89.0f)
		x += 180.0f;
	while (y < -180.0f)
		y += 360.0f;
	while (y > 180.0f)
		y -= 360.0f;

	z = 0.f;
}

void c_vector::clamp()
{
	while (this->x < -180.0f)
		this->x += 360.0f;

	while (this->x > 180.0f)
		this->x -= 360.0f;

	if (this->x > 89.0f)
		this->x = 89.0f;

	if (this->x < -89.0f)
		this->x = -89.0f;

	while (this->y < -180.0f)
		this->y += 360.0f;

	while (this->y > 180.0f)
		this->y -= 360.0f;

	this->z = 0.0f;
}

float c_vector::dot(const c_vector& other) const
{
	return (x * other.x + y * other.y + z * other.z);
}

float c_vector::dot(const float* other) const
{
	return (x * other[0] + y * other[1] + z * other[2]);
}

float c_vector::length_sqr() const
{
	return (x * x + y * y + z * z);
}

float c_vector::length_2d_sqr() const
{
	return (x * x + y * y);
}

float c_vector::length() const
{
	return sqrt(length_sqr());
}

float c_vector::length_2d() const
{
	return sqrt(length_2d_sqr());
}

float c_vector::distance_to(const c_vector& to) const
{
	return (*this - to).length();
}

bool c_vector::is_valid() const
{
	return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
}

float c_vector::operator[](int idx) const
{
	return ((float*)this)[idx];
}

float& c_vector::operator[](int idx)
{
	return ((float*)this)[idx];
}

c_vector& c_vector::operator=(const c_vector& other)
{
	x = other.x; y = other.y; z = other.z;

	return *this;
}

bool c_vector::operator==(const c_vector& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

c_vector c_vector::operator+(const c_vector& other) const
{
	return { x + other.x, y + other.y, z + other.z };
}

c_vector c_vector::operator-(const c_vector& other) const
{
	return { x - other.x, y - other.y, z - other.z };
}

c_vector c_vector::operator*(const c_vector& other) const
{
	return { x * other.x, y * other.y, z * other.z };
}

c_vector c_vector::operator/(const c_vector& other) const
{
	return { x / other.x, y / other.y, z / other.z };
}

c_vector c_vector::operator+(const float& other) const
{
	return { x + other, y + other, z + other };
}

c_vector c_vector::operator-(const float& other) const
{
	return { x - other, y - other, z - other };
}

c_vector c_vector::operator*(const float& other) const
{
	return { x * other, y * other, z * other };
}

c_vector c_vector::operator/(const float& other) const
{
	return { x / other, y / other, z / other };
}

c_vector& c_vector::operator+=(const c_vector& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

c_vector& c_vector::operator-=(const c_vector& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

c_vector& c_vector::operator*=(const c_vector& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

c_vector& c_vector::operator/=(const c_vector& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

c_vector& c_vector::operator+=(const float& other)
{
	x += other;
	y += other;
	z += other;
	return *this;
}

c_vector& c_vector::operator-=(const float& other)
{
	x -= other;
	y -= other;
	z -= other;
	return *this;
}

c_vector& c_vector::operator*=(const float& other)
{
	x *= other;
	y *= other;
	z *= other;
	return *this;
}

c_vector& c_vector::operator/=(const float& other)
{
	x /= other;
	y /= other;
	z /= other;
	return *this;
}

c_vector::operator std::string() const 
{
	return std::string("x: " + std::to_string(this->x) + " y: " + std::to_string(this->y) + " z: " + std::to_string(this->z));
}

c_vector_aligned::c_vector_aligned()
{
	x = y = z = w = 0.f;
}

c_vector_aligned::c_vector_aligned(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
	w = 0;
}

c_vector_aligned::c_vector_aligned(const c_vector& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = 0;
}

c_vector_aligned& c_vector_aligned::operator=(const c_vector& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = 0;

	return *this;
}

c_vector_2d::c_vector_2d()
{
	x = y = 0.f;
}