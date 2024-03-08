#pragma once

enum stereo_eye_t
{
	stereo_eye_mono = 0,
	stereo_eye_left = 1,
	stereo_eye_right = 2,
	stereo_eye_max = 3,
};

class c_view_setup
{
public:
	c_view_setup()
	{
		aspect_ratio = 0.0f;
		render_to_subrect_of_larger_screen = false;
		do_bloom_and_tone_mapping = true;
		ortho = false;
		off_center = false;
		cache_full_scene_state = false;
		view_to_projection_override = false;
		stereo_eye = stereo_eye_mono;
	}

	int			x;
	int			unscaled_x;
	int			y;
	int			unscaled_y;
	int			width;
	int			unscaled_width;
	int			height;
	stereo_eye_t stereo_eye;
	int			unscaled_height;
	bool		ortho;
	float		ortho_left;
	float		ortho_top;
	float		ortho_right;
	float		ortho_bottom;
	float		fov;
	float		fov_view_model;
	c_vector	origin;
	c_vector	angles;
	float		z_near;
	float		z_far;
	float		z_near_view_model;
	float		z_far_view_model;
	bool		render_to_subrect_of_larger_screen;
	float		aspect_ratio;
	bool		off_center;
	float		off_center_top;
	float		off_center_bottom;
	float		off_center_left;
	float		off_center_right;
	bool		do_bloom_and_tone_mapping;
	bool		cache_full_scene_state;
	bool        view_to_projection_override;
	D3DMATRIX   view_to_projection;
};