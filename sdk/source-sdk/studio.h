#pragma once

struct mstudiobbox_t
{
    int         bone;
    int         group;
    c_vector    bb_min;
    c_vector    bb_max;
    int         hitbox_name_index;
    int	        unused[8];
};

struct mstudiohitboxset_t
{
    int sz_name_index;
    int num_hitboxes;
    int hitbox_index;

    mstudiobbox_t* hitbox(int i) const 
    { 
        return (mstudiobbox_t*)(((unsigned char*)this) + hitbox_index) + i; 
    };
};

struct studiohdr_t
{
    int         id;
    int         version;
    long        checksum;
    char        name[64];
    int         length;
    c_vector    eye_pos;
    c_vector    illum_position;
    c_vector    hull_min;
    c_vector    hull_max;
    c_vector    view_bb_min;
    c_vector    view_bb_max;
    int         flags;
    int         num_bones;
    int         bone_index;
    int         num_bone_controllers;
    int         bone_controller_index;
    int         num_hitbox_sets;
    int         hitbox_set_index;

    mstudiohitboxset_t* hitbox_set(int i) const
    {
        return (mstudiohitboxset_t*)(((unsigned char*)this) + hitbox_set_index) + i;
    };
};