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
		m_b_render_to_subrect_of_larger_screen = false;
		m_b_do_bloom_and_tone_mapping = true;
		m_b_ortho = false;
		m_b_off_center = false;
		m_b_cache_full_scene_state = false;
		m_b_view_to_projection_override = false;
		m_e_stereo_eye = stereo_eye_mono;
	}

	int			x;
	int			m_n_unscaled_x;
	int			y;
	int			m_n_unscaled_y;
	int			width;
	int			m_n_unscaled_width;
	int			height;
	stereo_eye_t m_e_stereo_eye;
	int			m_n_unscaled_height;
	bool		m_b_ortho;
	float		m_ortho_left;
	float		m_ortho_top;
	float		m_ortho_right;
	float		m_ortho_bottom;
	float		fov;
	float		fov_view_model;
	c_vector	origin;
	c_vector	angles;
	float		z_near;
	float		z_far;
	float		z_near_view_model;
	float		z_far_view_model;
	bool		m_b_render_to_subrect_of_larger_screen;
	float		aspect_ratio;
	bool		m_b_off_center;
	float		m_fl_off_center_top;
	float		m_fl_off_center_bottom;
	float		m_fl_off_center_left;
	float		m_fl_off_center_right;
	bool		m_b_do_bloom_and_tone_mapping;
	bool		m_b_cache_full_scene_state;
	bool        m_b_view_to_projection_override;
	D3DMATRIX   view_to_projection;
};