#pragma once
#include "sdk/interfaces.h"
#include "utils/hotkey.h"

namespace globals
{
    inline bool unload = false;

    inline v_panel mat_system_top_panel = false;
    inline v_panel overlay_popup_panel = false;
    inline v_panel focus_overlay_panel = false;

    inline c_vector view_origin;

    inline D3DMATRIX world_to_screen;
    inline float fov = 0;
    inline void* menu_panel = nullptr;

    inline std::atomic<std::pair<bool, const char*>> waiting_to_be_executed;
}

namespace settings
{
    namespace menu
    {
        inline bool opened = false;
        inline bool custom_loading_screen = true;

        namespace colors
        {
            inline float window_bg[4]           = { 0.07f, 0.07f, 0.07f, 1.f };
            inline float child_bg[4]            = { 0.1f, 0.1f, 0.1f, 1.f };
            inline float text[4]                = { 0.4f, 0.4f, 0.4f, 1.f };
            inline float text_hovered[4]        = { 0.8f, 0.8f, 0.8f, 1.f };
            inline float text_active[4]         = { 1.f, 1.f, 1.f, 1.f };
            inline float frame_bg[4]            = { 0.2f, 0.2f, 0.2f, 1.f };
            inline float frame_hovered_bg[4]    = { 0.4f, 0.4f, 0.4f, 1.f };
            inline float frame_active_bg[4]     = { 1.f, 1.f, 1.f, 1.f };
        }
    }

    namespace aimbot
    {
        namespace globals
        {
            inline bool enable = false;
            inline hotkey_t hotkey;
            inline bool silent = false;
            inline bool automatic_fire = false;
            inline bool penetrate_walls = false;
            inline float fov = 0;
            inline int hitbox = 0;
            inline int priority = 0;
        }

        namespace accuracy
        {
            inline bool predict_spread = false;
            inline bool disable_recoil = false;
            inline bool disable_visual_recoil = false;
            inline float backtrack = 0;
            inline float smooth = 0.f;
        }

        namespace visuals
        {
            inline bool fov = false;
            inline bool snaplines = false;
            
            namespace backtrack
            {
                inline bool enable = false;
                inline int material_type = 0;
            }

            namespace colors
            {
                inline float fov[4]         = { 1.f, 1.f, 1.f, 1.f };
                inline float snaplines[4]   = { 1.f, 1.f, 1.f, 1.f };
                inline float backtrack[4]   = { 1.f, 1.f, 1.f, 1.f };
            }
        }
    }

    namespace antiaim
    {
        namespace globals
        {
            inline bool enable = false;
            inline hotkey_t hotkey;
            inline int yaw = 0;
            inline int pitch = 0;
            inline bool at_target = false;
            inline bool invert_yaw = false;
            inline bool fake_duck = false;
        }

        namespace fakelags
        {
            inline bool enable = false;
            inline int count = 1;
            inline int method = 0;
        }

        namespace visuals
        {
            namespace fake_model
            {
                inline bool enable = false;
                inline int material_type = 0;
            }

            namespace colors 
            {
                inline float fake_model[4] = { 1.f, 1.f, 1.f, 1.f };
            }
        }
    }

    namespace visuals
    {
        namespace players
        {
            inline bool enable = false;
            inline bool dormant = false;
            inline bool box = false;
            inline bool name = false;
            inline bool rp_team = false;
            inline bool user_group = false;
            inline bool weapon_name = false;
            inline bool distance = false;
            inline int render_distance = 15000;

            namespace colors
            {
                inline float box[4] = { 1.f, 1.f, 1.f, 1.f };
                inline float name[4] = { 1.f, 1.f, 1.f, 1.f };
                inline float rp_team[4] = { 1.f, 1.f, 1.f, 1.f };
                inline float user_group[4] = { 1.f, 1.f, 1.f, 1.f };
                inline float weapon_name[4] = { 1.f, 1.f, 1.f, 1.f };
                inline float distance[4] = { 1.f, 1.f, 1.f, 1.f };
            }
        }

        namespace entity
        {
            inline nlohmann::json list;

            inline bool enable = false;
            inline bool dormant = false;
            inline bool box = false;
            inline bool name = false;
            inline bool distance = false;
            inline int render_distance = 15000;

            namespace colors
            {
                inline float box[4] = { 1.f, 1.f, 1.f, 1.f };
                inline float name[4] = { 1.f, 1.f, 1.f, 1.f };
                inline float distance[4] = { 1.f, 1.f, 1.f, 1.f };
            }
        }
    }

    namespace miscellaneous
    {
        namespace globals
        {
            namespace third_person
            {
                inline bool enable = false;
                inline hotkey_t hotkey;
                inline int distance = 100;
            }
        }

        namespace movement
        {
            inline bool bhop = false;
            inline bool air_strafe = false;
        }
    }

    namespace lua
    {
        namespace miscellaneous
        {
            inline bool dumper = false;
            inline bool net_logger = false;
        }
    }
}