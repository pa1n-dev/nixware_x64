#pragma once
#include <cmath>

#include "vector.h"

namespace math
{
	constexpr float PI_F = 3.14159265358979323846f;
	constexpr double PI_D = 3.14159265358979323846;

	template <typename T>
	T rad2deg(T x);

	template <typename T>
	T deg2rad(T x);

	void angle_to_vectors(const q_angle& ang, c_vector& forward, c_vector& right, c_vector& up);
	void vector_to_angle(const c_vector& forward, q_angle& out);
	bool screen_transform(const c_vector& in, c_vector& out);
	bool world_to_screen(const c_vector& in, c_vector& out);
}