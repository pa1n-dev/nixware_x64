#pragma once
#include <cmath>

#include "vector.h"

namespace math
{
	constexpr float RAD_PI_F = 57.295779513082f;
	constexpr float PI_F = 3.14159265358979323846f;
	constexpr double PI_D = 3.14159265358979323846;

	template <typename T>
	T rad2deg(T x)
	{
		return static_cast<T>(static_cast<double>(x) * (180.0 / PI_D));
	}

	template <typename T>
	T deg2rad(T x)
	{
		return static_cast<T>(static_cast<double>(x) * (PI_D / 180.0));
	}

	void angle_to_vectors(const q_angle& ang, c_vector& forward, c_vector& right, c_vector& up);
	void angle_to_vector(const q_angle& ang, c_vector& forward);
	void vector_to_angle(const c_vector& forward, q_angle& out);
	void vector_transform(const c_vector& vector, const matrix3x4& matrix, c_vector& out);
	float normalize_yaw(float yaw);
	float normalize_pitch(float pitch);
	q_angle calc_angle(const c_vector& from, const c_vector& to);
}