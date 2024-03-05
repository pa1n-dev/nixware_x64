#include "math.h"

void math::angle_to_vectors(const q_angle& ang, c_vector& forward, c_vector& right, c_vector& up)
{
	float sr, sp, sy, cr, cp, cy;

	float rad_x = deg2rad(ang.x);
	float rad_y = deg2rad(ang.y);
	float rad_z = deg2rad(ang.z);

	sp = sin(rad_x); cp = cos(rad_x);
	sy = sin(rad_y); cy = cos(rad_y);
	sr = sin(rad_z); cr = cos(rad_z);

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;

	right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
	right.y = (-1 * sr * sp * sy + -1 * cr * cy);
	right.z = -1 * sr * cp;

	up.x = (cr * sp * cy + -sr * -sy);
	up.y = (cr * sp * sy + -sr * cy);
	up.z = cr * cp;
}

void math::angle_to_vector(const q_angle& ang, c_vector& forward)
{
	float sr, sp, sy, cr, cp, cy;

	float rad_x = deg2rad(ang.x);
	float rad_y = deg2rad(ang.y);
	float rad_z = deg2rad(ang.z);

	sp = sin(rad_x); cp = cos(rad_x);
	sy = sin(rad_y); cy = cos(rad_y);
	sr = sin(rad_z); cr = cos(rad_z);

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}

void math::vector_to_angle(const c_vector& forward, q_angle& out)
{
	float tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / PI_F);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / PI_F);
		if (pitch < 0)
			pitch += 360;
	}

	out[0] = pitch;
	out[1] = yaw;
	out[2] = 0;
}

void math::vector_transform(const c_vector& vector, const matrix3x4& matrix, c_vector& out)
{
	out[0] = vector.dot(matrix[0]) + matrix[0][3];
	out[1] = vector.dot(matrix[1]) + matrix[1][3];
	out[2] = vector.dot(matrix[2]) + matrix[2][3];
}