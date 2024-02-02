#pragma once

class c_radian_euler
{
public:
	float x, y, z;

	c_radian_euler();

	void make_inf();
	void make_zero();

	float& operator[](int i);
	float operator[](int i) const;

	bool operator==(const c_radian_euler& other) const;
	bool operator!=(const c_radian_euler& other) const;
};