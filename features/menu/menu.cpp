#include "menu.h"
#include "../lua/lua.h"

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
    PushStyleColor(ImGuiCol_TextHovered, ImVec4(settings::menu::colors::text_hovered[0], settings::menu::colors::text_hovered[1], settings::menu::colors::text_hovered[2], settings::menu::colors::text_hovered[3]));
    PushStyleColor(ImGuiCol_TextActive, ImVec4(settings::menu::colors::text_active[0], settings::menu::colors::text_active[1], settings::menu::colors::text_active[2], settings::menu::colors::text_active[3]));
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

        BeginChild(xorstr("Globals"), child_size);
        {
            Checkbox(xorstr("Enable"), &settings::aimbot::globals::enable); custom::hotkey(xorstr("Aimbot Hotkey"), &settings::aimbot::globals::hotkey);
            Checkbox(xorstr("Silent"), &settings::aimbot::globals::silent);
            Checkbox(xorstr("Automatic fire"), &settings::aimbot::globals::automatic_fire);
            Checkbox(xorstr("Penetrate walls"), &settings::aimbot::globals::penetrate_walls);
            SliderFloat(xorstr("Fov"), &settings::aimbot::globals::fov, 0.f, 180.f, xorstr("%.1f"), ImGuiSliderFlags_NoInput);
            Combo(xorstr("Hitbox"), &settings::aimbot::globals::hitbox, xorstr("Head\0" "Chest\0" "Stomach\0" "Hitscan\0"));
            Combo(xorstr("Priority"), &settings::aimbot::globals::priority, xorstr("Fov\0" "Distance\0" "Health\0"));
        }
        EndChild();

        SameLine();

        BeginChild(xorstr("Accuracy"), child_size);
        {
            Checkbox(xorstr("Predict spread"), &settings::aimbot::accuracy::predict_spread);
            Checkbox(xorstr("Disable recoil"), &settings::aimbot::accuracy::disable_recoil);
            Checkbox(xorstr("Disable visual recoil"), &settings::aimbot::accuracy::disable_visual_recoil);
            SliderFloat(xorstr("Backtrack"), &settings::aimbot::accuracy::backtrack, 0.f, 1.f, xorstr("%.3f ms"), ImGuiSliderFlags_NoInput);
            SliderFloat(xorstr("Smooth"), &settings::aimbot::accuracy::smooth, 0.f, 20.f, xorstr("%.1f"), ImGuiSliderFlags_NoInput);
        }
        EndChild();

        SameLine();

        BeginChild(xorstr("Visuals"), child_size);
        {
            Checkbox(xorstr("Fov"), &settings::aimbot::visuals::fov); ColorEdit4(xorstr("Fov"), settings::aimbot::visuals::colors::fov, color_edit4_flags);
            Checkbox(xorstr("Snaplines"), &settings::aimbot::visuals::snaplines); ColorEdit4(xorstr("Snaplines"), settings::aimbot::visuals::colors::snaplines, color_edit4_flags);
            Checkbox(xorstr("Backtrack"), &settings::aimbot::visuals::backtrack::enable); ColorEdit4(xorstr("Backtrack"), settings::aimbot::visuals::colors::backtrack, color_edit4_flags);
            Combo(xorstr("Material"), &settings::aimbot::visuals::backtrack::material_type, xorstr("Normal\0" "Flat\0" "Wireframe\0"));
        }
        EndChild();

        EndTabItem();
    }

    if (BeginTabItem(xorstr("AntiAim")))
    {
        ImVec2 child_size = ImVec2((GetColumnWidth() - (style.ItemSpacing.x * 2)) / 3, GetWindowHeight() - (GetCursorPosY() + style.ItemInnerSpacing.y * 2));

        BeginChild(xorstr("Globals"), child_size);
        {
            Checkbox(xorstr("Enable"), &settings::antihit::fake_angles::enable); custom::hotkey(xorstr("AntiAim Hotkey"), &settings::antihit::fake_angles::hotkey);
            Checkbox(xorstr("Fake duck"), &settings::antihit::fake_angles::fake_duck);
            Checkbox(xorstr("At target"), &settings::antihit::fake_angles::at_target);
            Checkbox(xorstr("Invert yaw"), &settings::antihit::fake_angles::invert_yaw);
            Combo(xorstr("Yaw"), &settings::antihit::fake_angles::yaw, xorstr("LBY\0"));
            Combo(xorstr("Pitch"), &settings::antihit::fake_angles::pitch, xorstr("Down\0" "Up\0"));
        }
        EndChild();

        SameLine();

        BeginChild(xorstr("Fake Lag's"), child_size);
        {
            Checkbox(xorstr("Enable"), &settings::antihit::fake_lags::enable);
            SliderInt(xorstr("Count"), &settings::antihit::fake_lags::count, 1, 24, xorstr("%d"), ImGuiSliderFlags_NoInput); /*sv_maxusrcmdprocessticks = 24*/
            Combo(xorstr("Method"), &settings::antihit::fake_lags::method, xorstr("On Ground\0" "In Air\0" "On Move\0" "On Stand\0" "Always\0"));
        }
        EndChild();

        SameLine();

        BeginChild(xorstr("Visuals"), child_size);
        {
            Checkbox(xorstr("Fake model"), &settings::antihit::visuals::fake_model::enable); ColorEdit4(xorstr("Fake model"), settings::antihit::visuals::colors::fake_model, color_edit4_flags);
            Combo(xorstr("Material"), &settings::antihit::visuals::fake_model::material_type, xorstr("Normal\0" "Flat\0" "Wireframe\0"));
        }
        EndChild();

        EndTabItem();
    }

    if (BeginTabItem(xorstr("Visuals")))
    {
        ImVec2 child_size = ImVec2((GetColumnWidth() - (style.ItemSpacing.x * 2)) / 3, GetWindowHeight() - (GetCursorPosY() + style.ItemInnerSpacing.y * 2));

        BeginChild(xorstr("ESP"), child_size);
        {
            static int type = 0;
            Combo(xorstr("##ESP"), &type, xorstr("Player\0" "Entity\0"));

            switch (type)
            {
            case 0:
            {
                Checkbox(xorstr("Enable"), &settings::visuals::esp::players::enable);
                Checkbox(xorstr("Dormant"), &settings::visuals::esp::players::dormant);
                Checkbox(xorstr("Box"), &settings::visuals::esp::players::box); ColorEdit4(xorstr("Box"), settings::visuals::esp::players::colors::box, color_edit4_flags);
                Checkbox(xorstr("Name"), &settings::visuals::esp::players::name); ColorEdit4(xorstr("Name"), settings::visuals::esp::players::colors::name, color_edit4_flags);
                Checkbox(xorstr("Rp team"), &settings::visuals::esp::players::rp_team); ColorEdit4(xorstr("Rp team"), settings::visuals::esp::players::colors::rp_team, color_edit4_flags);
                Checkbox(xorstr("User group"), &settings::visuals::esp::players::user_group); ColorEdit4(xorstr("User group"), settings::visuals::esp::players::colors::user_group, color_edit4_flags);
                Checkbox(xorstr("Weapon name"), &settings::visuals::esp::players::weapon_name); ColorEdit4(xorstr("Weapon name"), settings::visuals::esp::players::colors::weapon_name, color_edit4_flags);
                Checkbox(xorstr("Distance"), &settings::visuals::esp::players::distance); ColorEdit4(xorstr("Distance"), settings::visuals::esp::players::colors::distance, color_edit4_flags);
                SliderInt(xorstr("Render distance"), &settings::visuals::esp::players::render_distance, 100, 20000, xorstr("%d m"), ImGuiSliderFlags_NoInput);
            }
            break;
            case 1:
            {
                Checkbox(xorstr("Enable"), &settings::visuals::esp::entity::enable);
                Checkbox(xorstr("Dormant"), &settings::visuals::esp::entity::dormant);
                Checkbox(xorstr("Box"), &settings::visuals::esp::entity::box); ColorEdit4(xorstr("Box"), settings::visuals::esp::entity::colors::box, color_edit4_flags);
                Checkbox(xorstr("Name"), &settings::visuals::esp::entity::name); ColorEdit4(xorstr("Name"), settings::visuals::esp::entity::colors::name, color_edit4_flags);
                Checkbox(xorstr("Distance"), &settings::visuals::esp::entity::distance); ColorEdit4(xorstr("Distance"), settings::visuals::esp::entity::colors::distance, color_edit4_flags);

                if (BeginCombo(xorstr("List"), xorstr("...")))
                {
                    utilities::update_entity_list();

                    for (auto item : settings::visuals::esp::entity::list.items())
                    {
                        bool temp = item.value();
                        Selectable(item.key().c_str(), &temp, ImGuiSelectableFlags_DontClosePopups);
                        item.value() = temp;
                    }

                    EndCombo();
                }

                SliderInt(xorstr("Render distance"), &settings::visuals::esp::entity::render_distance, 100, 20000, xorstr("%d m"), ImGuiSliderFlags_NoInput);
            }
            break;
            }
        }
        EndChild();

        SameLine();

        BeginChild(xorstr("Chams"), child_size);
        {

        }
        EndChild();

        SameLine();

        BeginChild(xorstr("World"), child_size);
        {
            Checkbox(xorstr("Fov changer"), &settings::visuals::world::fov_changer::enable);
            SliderFloat(xorstr("Value##1"), &settings::visuals::world::fov_changer::value, 50, 179, xorstr("%.1f"), ImGuiSliderFlags_NoInput);

            Checkbox(xorstr("Model fov changer"), &settings::visuals::world::model_fov_changer::enable);
            SliderFloat(xorstr("Value##2"), &settings::visuals::world::model_fov_changer::value, 30, 150, xorstr("%.1f"), ImGuiSliderFlags_NoInput);
        }
        EndChild();

        EndTabItem();
    }

    if (BeginTabItem(xorstr("Misc")))
    {
        ImVec2 child_size = ImVec2((GetColumnWidth() - (style.ItemSpacing.x)) / 2, GetWindowHeight() - (GetCursorPosY() + style.ItemInnerSpacing.y * 2));

        BeginChild(xorstr("Globals"), child_size);
        {
            Checkbox(xorstr("ThirdPerson"), &settings::miscellaneous::globals::third_person::enable); custom::hotkey(xorstr("Third person Hotkey"), &settings::miscellaneous::globals::third_person::hotkey);
            SliderInt(xorstr("ThirdPerson Distance"), &settings::miscellaneous::globals::third_person::distance, 10, 200);
        }
        EndChild();

        SameLine();

        BeginChild(xorstr("Movement"), child_size);
        {
            Checkbox(xorstr("Bunny hop"), &settings::miscellaneous::movement::bhop);
            Checkbox(xorstr("Air strafe"), &settings::miscellaneous::movement::air_strafe);
        }
        EndChild();

        EndTabItem();
    }

    if (BeginTabItem(xorstr("Lua")))
    {
        ImVec2 child_size = ImVec2((GetColumnWidth() - (style.ItemSpacing.x * 2)) / 3, GetWindowHeight() - (GetCursorPosY() + style.ItemInnerSpacing.y * 2));

        static int selected_item = -1;
        static char search_buffer[256] = "";

        std::vector<std::string> file_list = utilities::get_files_from_folder(xorstr("C:/nixware/lua/"), search_buffer, xorstr(".lua"));

        BeginChild(xorstr("Scripts"), child_size);
        {
            float column_width = GetColumnWidth();

            PushItemWidth(column_width - 10.f);
            InputText(xorstr("Search"), search_buffer, sizeof(search_buffer));

            if (BeginListBox(xorstr("##Files"), ImVec2(0, GetWindowHeight() - (GetCursorPosY() + 10.f))))
            {
                for (int i = 0; i < file_list.size(); i++)
                {
                    if (Selectable(file_list[i].c_str(), selected_item == i, 0, ImVec2(column_width, 0)))
                        selected_item = i;
                }

                EndListBox();
            }

            PopItemWidth();
        }
        EndChild();

        SameLine();

        BeginChild(xorstr("Action"), child_size);
        {
            float column_width = GetColumnWidth();

            if (selected_item != -1 && selected_item < file_list.size())
            {
                std::string path = xorstr("C:/nixware/lua/") + file_list[selected_item] + xorstr(".lua");

                LabelText(file_list[selected_item].c_str());
                LabelText("Last update:", utilities::get_last_modified_time(path).c_str());

                if (Button(xorstr("Load script"), ImVec2(column_width - 10.f, 35.f)))
                    globals::waiting_to_be_executed.store(std::make_pair(true, path.c_str()));
            }
        }
        EndChild();

        SameLine();

        BeginChild(xorstr("Misc"), child_size);
        {
            Checkbox(xorstr("Dumper"), &settings::lua::miscellaneous::dumper);
            Checkbox(xorstr("NetLogger"), &settings::lua::miscellaneous::net_logger);

        }
        EndChild();

        EndTabItem();
    }

    if (BeginTabItem(xorstr("Settings")))
    {
        ImVec2 child_size = ImVec2((GetColumnWidth() - (style.ItemSpacing.x * 2)) / 3, GetWindowHeight() - (GetCursorPosY() + style.ItemInnerSpacing.y * 2));

        BeginChild(xorstr("Info"), child_size);
        {
            LabelText(xorstr("Last update:"), __DATE__);
        }
        EndChild();

        SameLine();

        BeginChild(xorstr("Menu"), child_size);
        {
            LabelText(xorstr("WindowBg"));       ColorEdit4(xorstr("WindowBg"), settings::menu::colors::window_bg, color_edit4_flags);
            LabelText(xorstr("ChildBg"));        ColorEdit4(xorstr("ChildBg"), settings::menu::colors::child_bg, color_edit4_flags);
            LabelText(xorstr("Text"));           ColorEdit4(xorstr("Text"), settings::menu::colors::text, color_edit4_flags);
            LabelText(xorstr("TextHovered"));    ColorEdit4(xorstr("TextHovered"), settings::menu::colors::text_hovered, color_edit4_flags);
            LabelText(xorstr("TextActive"));     ColorEdit4(xorstr("TextActive"), settings::menu::colors::text_active, color_edit4_flags);
            LabelText(xorstr("FrameBg"));        ColorEdit4(xorstr("FrameBg"), settings::menu::colors::frame_bg, color_edit4_flags);
            LabelText(xorstr("FrameHoveredBg")); ColorEdit4(xorstr("FrameHoveredBg"), settings::menu::colors::frame_hovered_bg, color_edit4_flags);
            LabelText(xorstr("FrameActiveBg"));  ColorEdit4(xorstr("FrameActiveBg"), settings::menu::colors::frame_active_bg, color_edit4_flags);
            Checkbox(xorstr("Custom loading screen"), &settings::menu::custom_loading_screen::enable);
            SetNextItemWidth(GetColumnWidth() - 10.f);
            InputText(xorstr("Url"), settings::menu::custom_loading_screen::url, IM_ARRAYSIZE(settings::menu::custom_loading_screen::url));
        }
        EndChild();

        SameLine();

        BeginChild(xorstr("Configs"), child_size);
        {
            float column_width = GetColumnWidth() - 10.f;
            ImVec2 button_size = ImVec2((column_width / 2) - style.ItemInnerSpacing.x, 35.f);

            static int selected_item = -1;
            static std::string selected_config_name;

            static char new_config_name[256] = "";

            std::vector<std::string> file_list = utilities::get_files_from_folder(xorstr("C:/nixware/configs/"), "", xorstr(".nixware"));

            if (BeginCombo(xorstr("Configs"), selected_config_name.empty() ? xorstr("...") : selected_config_name.c_str()))
            {
                for (int i = 0; i < file_list.size(); i++)
                {
                    const bool is_selected = (selected_item == i);

                    if (Selectable(file_list[i].c_str(), is_selected))
                    {
                        selected_item = i;
                        selected_config_name = file_list[i];
                    }

                    if (is_selected)
                        SetItemDefaultFocus();
                }

                EndCombo();
            }

            if (Button(xorstr("Load"), button_size))
                config_manager::load(selected_config_name);

            SameLine();

            if (Button(xorstr("Save"), button_size))
                config_manager::save(selected_config_name);

            SetNextItemWidth(column_width);
            InputText(xorstr("New config name"), new_config_name, IM_ARRAYSIZE(new_config_name));

            if (Button(xorstr("Create and save"), ImVec2(column_width, 35.f)))
                config_manager::save(new_config_name);

            if (Button(xorstr("Unload cheat"), ImVec2(column_width, 35.f)))
                globals::unload = true;
        }
        EndChild();

        EndTabItem();
    }

    EndTabBar();
    End();

    PopStyleColor(9);
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
    ImFormatString(context_name, sizeof(context_name), "HotKeyContext%s", label);

    char text[64] = { };
    ImFormatString(text, sizeof(text), "[  %s  ]", (hotkey->key != 0 && g.ActiveId != id) ? key_names[hotkey->key] : (g.ActiveId == id) ? "WAIT KEY" : "NONE");

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