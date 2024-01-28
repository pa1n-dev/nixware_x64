#pragma once

enum trace_type_t
{
	trace_everything = 0,
	trace_world_only,
	trace_entities_only,
	trace_everything_filter_props,
};

struct cplane_t
{
	c_vector		normal;
	float			dist;
	unsigned char	type;
	unsigned char	signbits;
	unsigned char	pad[2];
};

struct csurface_t
{
	const char*		name;
	short			surface_props;
	unsigned short	flags;
};

struct trace_t
{
	c_vector		start;
	c_vector		end;
	cplane_t		plane;
	float			fraction;
	int				contents;
	unsigned short	disp_flags;
	bool			all_solid;
	bool			start_solid;
	float			fraction_left_solid;
	csurface_t		surface;
	int				hit_group;
	short			physics_bone;
	void*			entity;
	int				hitbox;
};

struct ray_t
{
	ray_t() : unknown(nullptr), is_ray(false), is_swept(false) {}

	c_vector_aligned	start;
	c_vector_aligned	delta;
	c_vector_aligned	start_offset;
	c_vector_aligned	extents;
	const void*			unknown;
	bool				is_ray;
	bool				is_swept;

	ray_t(c_vector start, c_vector end) 
	{
		init(start, end);
	}

	void init(c_vector _start, c_vector _end)
	{
		delta = _end - _start;
		is_swept = (delta.length() != 0);
		unknown = nullptr;
		is_ray = true;
		start = _start;
	}
};

class i_trace_filter
{
public:
	virtual bool			should_hit_entity(void* entity, int mask) = 0;
	virtual trace_type_t	get_trace_type() const = 0;
};

class c_trace_filter : public i_trace_filter
{
public:
	bool should_hit_entity(void* entity, int contents_mask)
	{
		return !(entity == skip);
	}

	virtual trace_type_t get_trace_type() const
	{
		return trace_everything;
	}

	void* skip;
};

class i_engine_trace
{
public:
	void trace_ray(const ray_t& ray, unsigned int mask, i_trace_filter* filter, trace_t* trace)
	{
		return memory::call_v_function<void(__thiscall*)(void*, const ray_t&, unsigned int, i_trace_filter*, trace_t*)>(this, 4)(this, ray, mask, filter, trace);
	}
};