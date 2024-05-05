#pragma once
#include <string>

using matrix3x4 = float[3][4];
using matrix4x4 = float[16];

struct box_t
{
	float left, top, right, bottom;
};

class c_vector
{
public:
	float x, y, z;

	c_vector();
	c_vector(float _x, float _y, float _z);

	void make_inf();
	void make_zero();

	void normalize();
	c_vector normalized();
	void clamp();

	float dot(const c_vector& other) const;
	float dot(const float* other) const;

	float length_sqr() const;
	float length_2d_sqr() const;
	float length() const;
	float length_2d() const;
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

	c_vector operator+(const float& other) const;
	c_vector operator-(const float& other) const;
	c_vector operator*(const float& other) const;
	c_vector operator/(const float& other) const;

	c_vector& operator+=(const c_vector& other);
	c_vector& operator-=(const c_vector& other);
	c_vector& operator*=(const c_vector& other);
	c_vector& operator/=(const c_vector& other);

	c_vector& operator+=(const float& other);
	c_vector& operator-=(const float& other);
	c_vector& operator*=(const float& other);
	c_vector& operator/=(const float& other);

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

class c_vector_2d
{
public:
	float x, y;

	c_vector_2d();
};

using q_angle = c_vector;