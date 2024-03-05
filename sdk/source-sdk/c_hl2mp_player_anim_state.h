#pragma once

class c_animation_layer
{
public:
    int     sequence;
    float   prev_cycle;
    float   weight;
    int     order;

    float   playback_rate;
    float   cycle;

    float   layer_animtime;
    float   layer_fade_outtime;
    float   blend_in;
    float   blend_out;

    bool    client_blend;
};

struct gesture_slot_t
{
    int                 gesture_slot;
    int                 activity;
    bool                auto_kill;
    bool                active;
    c_animation_layer*  animation_layer;
};

struct debug_player_anim_data_t
{
    float       speed;
    float       aim_pitch;
    float       aim_yaw;
    float       body_height;
    c_vector_2d move_yaw;

    void init()
    {
        speed = 0.0f;
        aim_pitch = 0.0f;
        aim_yaw = 0.0f;
        body_height = 0.0f;
    }
};

struct multi_player_pose_data_t
{
    int move_x;
    int move_y;
    int aim_yaw;
    int aim_pitch;
    int body_height;
    int move_yaw;
    int move_scale;

    float estimate_yaw;
    float last_aim_turn_time;

    void init()
    {
        move_x = 0;
        move_y = 0;
        aim_yaw = 0;
        aim_pitch = 0;
        body_height = 0;
        move_yaw = 0;
        move_scale = 0;
        estimate_yaw = 0.0f;
        last_aim_turn_time = 0.0f;
    }
};

struct multi_player_movement_data_t
{
    float walk_speed;
    float run_speed;
    float sprint_speed;
    float body_yaw_rate;
};

class c_hl2mp_player_anim_state : public c_multiplayer_anim_state
{
public:
    char                            pad[8];
    bool                            force_aim_yaw;
    c_utl_vector<gesture_slot_t>    gesture_slots;
    void*                           player;
    q_angle                         ang_render;
    bool                            pose_parameter_init;
    multi_player_pose_data_t        pose_parameter_data;
    debug_player_anim_data_t        debug_anim_data;
    bool                            current_feet_yaw_initialized;
    float                           last_animation_state_clear_time;
    float                           eye_yaw;
    float                           eye_pitch;
    float                           goal_feet_yaw;
    float                           current_feet_yaw;
    float                           last_aim_turn_time;
    multi_player_movement_data_t    movement_data;
    bool                            jumping;
    float                           jump_start_time;
    bool                            first_jump_frame;
    bool                            in_swim;
    bool                            first_swim_frame;
    bool                            dying;
    bool                            first_dying_frame;
    int                             current_main_sequence_activity;
    int                             specific_main_sequence;
    void*                           active_weapon;
    float                           last_ground_speed_update_time;
};