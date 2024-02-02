#pragma once
#include <cmath>

#include "vector.h"

namespace math
{
	constexpr float PI_F = 3.14159265358979323846f;
	constexpr double PI_D = 3.14159265358979323846;

	template <typename T>
	T rad2deg(T x)
	{
		return x * (static_cast<T>(180) / static_cast<T>(PI_F));
	}

	template <typename T>
	T deg2rad(T x)
	{
		return x * (static_cast<T>(PI_F) / static_cast<T>(180));
	}

	void angle_to_vectors(const q_angle& ang, c_vector& forward, c_vector& right, c_vector& up);
	void angle_to_vector(const q_angle& ang, c_vector& forward);
	void vector_to_angle(const c_vector& forward, q_angle& out);
	void vector_transform(const c_vector& vector, const matrix3x4_t& matrix, c_vector& out);
}