#pragma once
#include <string>

using matrix3x4_t = float[3][4];
using matrix4x4_t = float[16];

class c_vector
{
public:
	float x, y, z;

	c_vector();
	c_vector(float _x, float _y, float _z);

	void make_inf();
	void make_zero();

	void normalize();
	void clamp();

	float dot(const c_vector& other) const;
	float dot(const float* other) const;

	float length() const;
	float length2d() const;
	float distance_to(const c_vector& to) const;

	bool is_valid() const;

	float operator[] (int index) const;
	float& operator[] (int index);

	c_vector& operator=(const c_vector& other);
	bool operator==(const c_vector& other) const;

	c_vector operator+(const c_vector& other) const;
	c_vector operator-(const c_vector& other) const;
	c_vector operator*(const c_vector& other) const;
	c_vector operator/(const c_vector& other) const;

	c_vector operator+(float other) const;
	c_vector operator-(float other) const;
	c_vector operator*(float other) const;
	c_vector operator/(float other) const;

	c_vector& operator+=(const c_vector& other);
	c_vector& operator-=(const c_vector& other);
	c_vector& operator*=(const c_vector& other);
	c_vector& operator/=(const c_vector& other);

	operator std::string() const;
};

class c_vector_aligned : public c_vector 
{
public:
	c_vector_aligned();
	c_vector_aligned(float _x, float _y, float _z);
	c_vector_aligned(const c_vector& other);

	c_vector_aligned& operator=(const c_vector& other);

	float w;
};

using q_angle = c_vector;