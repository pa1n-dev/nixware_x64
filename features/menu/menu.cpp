#include "menu.h"

void menu::render()
{
    if (!settings::menu::opened)
        return;
    
    ImGuiIO& io = GetIO();
    ImGuiStyle& style = GetStyle();

    PushStyleColor(ImGuiCol_WindowBg, ImVec4(settings::menu::colors::window_bg[0], settings::menu::colors::window_bg[1], settings::menu::colors::window_bg[2], settings::menu::colors::window_bg[3]));
    PushStyleColor(ImGuiCol_PopupBg, ImVec4(settings::menu::colors::window_bg[0], settings::menu::colors::window_bg[1], settings::menu::colors::window_bg[2], settings::menu::colors::window_bg[3]));
    PushStyleColor(ImGuiCol_ChildBg, ImVec4(settings::menu::colors::child_bg[0], settings::menu::colors::child_bg[1], settings::menu::colors::child_bg[2], settings::menu::colors::child_bg[3]));
    PushStyleColor(ImGuiCol_Text, ImVec4(settings::menu::colors::text[0], settings::menu::colors::text[1], settings::menu::colors::text[2], settings::menu::colors::text[3]));
    PushStyleColor(ImGuiCol_FrameBg, ImVec4(settings::menu::colors::frame_bg[0], settings::menu::colors::frame_bg[1], settings::menu::colors::frame_bg[2], settings::menu::colors::frame_bg[3]));
    PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(settings::menu::colors::frame_hovered_bg[0], settings::menu::colors::frame_hovered_bg[1], settings::menu::colors::frame_hovered_bg[2], settings::menu::colors::frame_hovered_bg[3]));
    PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(settings::menu::colors::frame_active_bg[0], settings::menu::colors::frame_active_bg[1], settings::menu::colors::frame_active_bg[2], settings::menu::colors::frame_active_bg[3]));

    PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(720, 355));

    SetNextWindowPos(ImVec2(io.DisplaySize.x / 2.f, io.DisplaySize.y / 2.f), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
    SetNextWindowSize(ImVec2(720, 355), ImGuiCond_Once);

    if (!Begin(xorstr("Nixware"), NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar))
        return;

    BeginTabBar(xorstr("Tabs"));

    if (BeginTabItem(xorstr("Aimbot")))
    {
        ImVec2 child_size = ImVec2((GetColumnWidth() - (style.ItemSpacing.x * 2)) / 3, GetWindowHeight() - (GetCursorPosY() + style.ItemInnerSpacing.y * 2));

        if (BeginChild(xorstr("Globals"), child_size))
        {
            Checkbox(xorstr("Enable"), &settings::aimbot::globals::enable); custom::hotkey(xorstr("Aimbot Hotkey"), &settings::aimbot::globals::hotkey);
            Checkbox(xorstr("Silent"), &settings::aimbot::globals::silent);
            Checkbox(xorstr("Automatic fire"), &settings::aimbot::globals::automatic_fire);
            SliderFloat(xorstr("Fov"), &settings::aimbot::globals::fov, 0.f, 180.f, xorstr("%.1f"), ImGuiSliderFlags_NoInput);
            Combo(xorstr("Hitbox"), &settings::aimbot::globals::hitbox, xorstr("Head\0" "Chest\0" "Stomach\0" "Hitscan\0"));
            Combo(xorstr("Priority"), &settings::aimbot::globals::priority, xorstr("Fov\0" "Distance\0" "Health\0"));

            EndChild();
        }

        SameLine();

        if (BeginChild(xorstr("Accuracy"), child_size))
        {
            Checkbox(xorstr("Predict spread"), &settings::aimbot::accuracy::predict_spread);
            Checkbox(xorstr("Disable recoil"), &settings::aimbot::accuracy::disable_recoil);
            SliderFloat(xorstr("Backtrack"), &settings::aimbot::accuracy::backtrack, 0.f, 1.f, xorstr("%.3f ms"), ImGuiSliderFlags_NoInput);
            SliderFloat(xorstr("Smooth"), &settings::aimbot::accuracy::smooth, 0.f, 20.f, xorstr("%.1f"), ImGuiSliderFlags_NoInput);

            EndChild();
        }

        SameLine();

        if (BeginChild(xorstr("Visuals"), child_size))
        {
            Checkbox(xorstr("Fov"), &settings::aimbot::visuals::fov); ColorEdit4(xorstr("Fov"), settings::aimbot::visuals::colors::fov, color_edit4_flags);
            Checkbox(xorstr("Snaplines"), &settings::aimbot::visuals::snaplines); ColorEdit4(xorstr("Snaplines"), settings::aimbot::visuals::colors::snaplines, color_edit4_flags);
            Checkbox(xorstr("Backtrack"), &settings::aimbot::visuals::backtrack);

            EndChild();
        }

        EndTabItem();
    }

    if (BeginTabItem(xorstr("AntiAim")))
    {
        ImVec2 child_size = ImVec2((GetColumnWidth() - (style.ItemSpacing.x * 2)) / 3, GetWindowHeight() - (GetCursorPosY() + style.ItemInnerSpacing.y * 2));

        if (BeginChild(xorstr("AntiAim"), child_size))
        {

            EndChild();
        }

        SameLine();

        if (BeginChild(xorstr("FakeLag's"), child_size))
        {

            EndChild();
        }

        SameLine();

        if (BeginChild(xorstr("Visuals"), child_size))
        {

            EndChild();
        }

        EndTabItem();
    }

    if (BeginTabItem(xorstr("Visuals")))
    {
        ImVec2 child_size = ImVec2((GetColumnWidth() - (style.ItemSpacing.x * 2)) / 3, GetWindowHeight() - (GetCursorPosY() + style.ItemInnerSpacing.y * 2));

        if (BeginChild(xorstr("Players"), child_size))
        {
            Checkbox(xorstr("Enable"), &settings::visuals::players::enable);
            Checkbox(xorstr("Dormant"), &settings::visuals::players::dormant);
            Checkbox(xorstr("Box"), &settings::visuals::players::box); ColorEdit4(xorstr("Box Color"), settings::visuals::players::colors::box, color_edit4_flags);

            EndChild();
        }

        SameLine();

        if (BeginChild(xorstr("Entity"), child_size))
        {
            Checkbox(xorstr("Enable"), &settings::visuals::entity::enable);

            EndChild();
        }

        SameLine();

        if (BeginChild(xorstr("Misc"), child_size))
        {

            EndChild();
        }

        EndTabItem();
    }

    if (BeginTabItem(xorstr("Misc")))
    {
        ImVec2 child_size = ImVec2((GetColumnWidth() - (style.ItemSpacing.x)) / 2, GetWindowHeight() - (GetCursorPosY() + style.ItemInnerSpacing.y * 2));

        if (BeginChild(xorstr("Globals"), child_size))
        {

            EndChild();
        }

        SameLine();

        if (BeginChild(xorstr("Movement"), child_size))
        {

            EndChild();
        }

        EndTabItem();
    }

    if (BeginTabItem(xorstr("Lua")))
    {

        EndTabItem();
    }

    if (BeginTabItem(xorstr("Settings")))
    {
        ImVec2 child_size = ImVec2((GetColumnWidth() - (style.ItemSpacing.x * 2)) / 3, GetWindowHeight() - (GetCursorPosY() + style.ItemInnerSpacing.y * 2));

        if (BeginChild(xorstr("Info"), child_size))
        {
            LabelText("Last update:", __DATE__);

            EndChild();
        }

        SameLine();

        if (BeginChild(xorstr("Menu"), child_size))
        {
            LabelText(xorstr("WindowBg"));       ColorEdit4(xorstr("WindowBg"), settings::menu::colors::window_bg, color_edit4_flags);
            LabelText(xorstr("ChildBg"));        ColorEdit4(xorstr("ChildBg"), settings::menu::colors::child_bg, color_edit4_flags);
            LabelText(xorstr("Text"));           ColorEdit4(xorstr("Text"), settings::menu::colors::text, color_edit4_flags);
            LabelText(xorstr("FrameBg"));        ColorEdit4(xorstr("FrameBg"), settings::menu::colors::frame_bg, color_edit4_flags);
            LabelText(xorstr("FrameHoveredBg")); ColorEdit4(xorstr("FrameHoveredBg"), settings::menu::colors::frame_hovered_bg, color_edit4_flags);
            LabelText(xorstr("FrameActiveBg"));  ColorEdit4(xorstr("FrameActiveBg"), settings::menu::colors::frame_active_bg, color_edit4_flags);
            Checkbox(xorstr("Custom loading screen"), &settings::menu::custom_loading_screen);

            EndChild();
        }

        SameLine();

        if (BeginChild(xorstr("Configs"), child_size))
        {
            float column_width = GetColumnWidth() - 10.f;

            if (ImGui::Button(xorstr("Unload cheat"), ImVec2(column_width, 35.f)))
                hooks::unhook();

            EndChild();
        }

        EndTabItem();
    }

    EndTabBar();
    End();

    PopStyleColor(7);
    PopStyleVar();
}

void menu::custom::hotkey(const char* label, hotkey_t* hotkey)
{
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return;

    SameLine();

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);

    const float width = GetColumnWidth();
    const ImVec2 pos = window->DC.CursorPos;

    char context_name[64] = { };
    sprintf(context_name, "HotKeyContext%s", label);

    char text[64] = { };
    sprintf_s(text, sizeof(text), "[  %s  ]", hotkey->key != 0 && g.ActiveId != id ? key_names[hotkey->key] : g.ActiveId == id ? "WAIT KEY" : "NONE");
    const ImVec2 text_size = CalcTextSize(text, NULL, true);

    const ImRect total_bb(ImVec2(pos.x + width - (text_size.x + 10.f), pos.y - style.FramePadding.y), ImVec2(pos.x + width, pos.y + text_size.y));

    ItemSize(total_bb);
    if (!ItemAdd(total_bb, id))
        return;

    const bool hovered = ItemHoverable(total_bb, id);
    if (hovered)
        SetHoveredID(id);

    if (hovered && (g.IO.MouseClicked[0] || g.IO.MouseDoubleClicked[0]))
    {
        if (g.ActiveId != id)
        {
            memset(g.IO.MouseDown, 0, sizeof(g.IO.MouseDown));
            memset(g.IO.KeysDown, 0, sizeof(g.IO.KeysDown));
            hotkey->key = 0;
        }

        SetActiveID(id, window);
    }

    bool changed = false;
    if (int key = hotkey->key; g.ActiveId == id)
    {
        for (int n = 0; n < IM_ARRAYSIZE(g.IO.MouseDown); n++)
        {
            if (IsMouseDown(n))
            {
                switch (n)
                {
                case 0:
                    key = VK_LBUTTON;
                    break;
                case 1:
                    key = VK_RBUTTON;
                    break;
                case 2:
                    key = VK_MBUTTON;
                    break;
                case 3:
                    key = VK_XBUTTON1;
                    break;
                case 4:
                    key = VK_XBUTTON2;
                    break;
                }

                changed = true;
                ClearActiveID();
            }
        }

        if (!changed)
        {
            for (int n = VK_BACK; n <= VK_RMENU; n++)
            {
                if (IsKeyDown((ImGuiKey)n))
                {
                    key = n;
                    changed = true;
                    ClearActiveID();
                }
            }
        }

        if (IsKeyPressed(ImGuiKey_Escape))
        {
            hotkey->key = 0;
            ClearActiveID();
        }
        else
            hotkey->key = key;
    }

    RenderText(total_bb.Min, text);

    PushStyleColor(ImGuiCol_PopupBg, ImVec4(0, 0, 0, 0));
    PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(80, 65));
    PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5, 5));

    if (BeginPopupContextItem(context_name))
    {
        SetWindowPos(ImVec2(total_bb.Min.x, total_bb.Max.y));

        if (Selectable("Always on", hotkey->type == hotkey_t::always_on))
            hotkey->type = hotkey_t::always_on;

        if (Selectable("Hold", hotkey->type == hotkey_t::hold))
            hotkey->type = hotkey_t::hold;

        if (Selectable("Toggle", hotkey->type == hotkey_t::toggle))
            hotkey->type = hotkey_t::toggle;

        if (Selectable("Force disable", hotkey->type == hotkey_t::force_disable))
            hotkey->type = hotkey_t::force_disable;

        End();
    }

    PopStyleColor();
    PopStyleVar(2);
}