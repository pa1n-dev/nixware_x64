#pragma once
#include <string>

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

	c_vector& operator+=(const c_vector& other);
	c_vector& operator-=(const c_vector& other);
	c_vector& operator*=(const c_vector& other);
	c_vector& operator/=(const c_vector& other);

	operator std::string() const;
};

using q_angle = c_vector;