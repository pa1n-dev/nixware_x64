#pragma once

class c_quaternion
{
public:
	float x, y, z, w;

	c_quaternion();

	void make_inf();
	void make_zero();

	float& operator[](int i);
	float operator[](int i) const;

	bool operator==(const c_quaternion& other) const;
	bool operator!=(const c_quaternion& other) const;
};