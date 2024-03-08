#pragma once
#include "sdk/interfaces.h"
#include "utils/hotkey.h"

namespace globals
{
    inline v_panel mat_system_top_panel = false;
    inline v_panel overlay_popup_panel = false;
    inline D3DMATRIX world_to_screen;
    inline float fov = 0;
}

namespace settings
{
    namespace menu
    {
        inline bool opened = false;

        namespace colors
        {
            inline float window_bg[4]           = { 0.07f, 0.07f, 0.07f, 1.f };
            inline float child_bg[4]            = { 0.1f, 0.1f, 0.1f, 1.f };
            inline float text[4]                = { 1.f, 1.f, 1.f, 1.f };
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
            inline float fov = 0;
            inline int hitbox = 0;
            inline int priority = 0;
        }

        namespace accuracy
        {
            inline bool predict_spread = false;
            inline bool disable_recoil = false;
            inline float backtrack = 0;
            inline float smooth = 0.f;
        }

        namespace visuals
        {
            inline bool fov = false;
            inline bool snaplines = false;
            inline bool backtrack = false;

            namespace colors
            {
                inline float fov[4] = { 1.f, 1.f, 1.f, 1.f };
                inline float snaplines[4] = { 1.f, 1.f, 1.f, 1.f };
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

            namespace colors
            {
                inline float box[4] = { 1.f, 1.f, 1.f, 1.f };
            }
        }

        namespace entity
        {
            inline bool enable = false;
        }
    }
}