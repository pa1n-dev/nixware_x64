#include "menu.h"

void menu::render()
{
    if (!settings::menu::opened)
        return;
    
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(settings::menu::colors::window_bg[0], settings::menu::colors::window_bg[1], settings::menu::colors::window_bg[2], settings::menu::colors::window_bg[3]));
    ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(settings::menu::colors::window_bg[0], settings::menu::colors::window_bg[1], settings::menu::colors::window_bg[2], settings::menu::colors::window_bg[3]));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(settings::menu::colors::child_bg[0], settings::menu::colors::child_bg[1], settings::menu::colors::child_bg[2], settings::menu::colors::child_bg[3]));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(settings::menu::colors::text[0], settings::menu::colors::text[1], settings::menu::colors::text[2], settings::menu::colors::text[3]));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(settings::menu::colors::frame_bg[0], settings::menu::colors::frame_bg[1], settings::menu::colors::frame_bg[2], settings::menu::colors::frame_bg[3]));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(settings::menu::colors::frame_hovered_bg[0], settings::menu::colors::frame_hovered_bg[1], settings::menu::colors::frame_hovered_bg[2], settings::menu::colors::frame_hovered_bg[3]));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(settings::menu::colors::frame_active_bg[0], settings::menu::colors::frame_active_bg[1], settings::menu::colors::frame_active_bg[2], settings::menu::colors::frame_active_bg[3]));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(720, 355));

    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x / 2.f, io.DisplaySize.y / 2.f), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(720, 355), ImGuiCond_Once);

    if (ImGui::Begin(xorstr("Nixware"), NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::BeginTabBar(xorstr("Tabs"));

        if (ImGui::BeginTabItem(xorstr("Aimbot")))
        {
            ImVec2 child_size = ImVec2((ImGui::GetColumnWidth() - (style.ItemSpacing.x * 2)) / 3, ImGui::GetWindowHeight() - (ImGui::GetCursorPosY() + style.ItemInnerSpacing.y * 2));

            if (ImGui::BeginChild(xorstr("Globals"), child_size))
            {
                ImGui::EndChild();
            }

            ImGui::SameLine();

            if (ImGui::BeginChild(xorstr("Accuracy"), child_size))
            {

                ImGui::EndChild();
            }

            ImGui::SameLine();

            if (ImGui::BeginChild(xorstr("Visuals"), child_size))
            {

                ImGui::EndChild();
            }

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(xorstr("AntiAim")))
        {
            ImVec2 child_size = ImVec2((ImGui::GetColumnWidth() - (style.ItemSpacing.x * 2)) / 3, ImGui::GetWindowHeight() - (ImGui::GetCursorPosY() + style.ItemInnerSpacing.y * 2));

            if (ImGui::BeginChild(xorstr("AntiAim"), child_size))
            {

                ImGui::EndChild();
            }

            ImGui::SameLine();

            if (ImGui::BeginChild(xorstr("FakeLag's"), child_size))
            {

                ImGui::EndChild();
            }

            ImGui::SameLine();

            if (ImGui::BeginChild(xorstr("Visuals"), child_size))
            {

                ImGui::EndChild();
            }

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(xorstr("Visuals")))
        {
            ImVec2 child_size = ImVec2((ImGui::GetColumnWidth() - (style.ItemSpacing.x * 2)) / 3, ImGui::GetWindowHeight() - (ImGui::GetCursorPosY() + style.ItemInnerSpacing.y * 2));

            if (ImGui::BeginChild(xorstr("Players"), child_size))
            {
                ImGui::Checkbox(xorstr("Enable"), &settings::visuals::players::enable);
                ImGui::Checkbox(xorstr("Dormant"), &settings::visuals::players::dormant);

                ImGui::EndChild();
            }

            ImGui::SameLine();

            if (ImGui::BeginChild(xorstr("Entity"), child_size))
            {
                ImGui::Checkbox(xorstr("Enable"), &settings::visuals::entity::enable);

                ImGui::EndChild();
            }

            ImGui::SameLine();

            if (ImGui::BeginChild(xorstr("Misc"), child_size))
            {

                ImGui::EndChild();
            }

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(xorstr("Misc")))
        {
            ImVec2 child_size = ImVec2((ImGui::GetColumnWidth() - (style.ItemSpacing.x)) / 2, ImGui::GetWindowHeight() - (ImGui::GetCursorPosY() + style.ItemInnerSpacing.y * 2));

            if (ImGui::BeginChild(xorstr("Globals"), child_size))
            {

                ImGui::EndChild();
            }

            ImGui::SameLine();

            if (ImGui::BeginChild(xorstr("Movement"), child_size))
            {

                ImGui::EndChild();
            }

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(xorstr("Lua")))
        {

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(xorstr("Settings")))
        {
            ImVec2 child_size = ImVec2((ImGui::GetColumnWidth() - (style.ItemSpacing.x * 2)) / 3, ImGui::GetWindowHeight() - (ImGui::GetCursorPosY() + style.ItemInnerSpacing.y * 2));

            if (ImGui::BeginChild(xorstr("Info"), child_size))
            {
                ImGui::LabelText("Last update:", __DATE__);

                ImGui::EndChild();
            }

            ImGui::SameLine();

            if (ImGui::BeginChild(xorstr("Menu"), child_size))
            {
                ImGui::LabelText(xorstr("WindowBg"));       ImGui::ColorEdit4(xorstr("WindowBg"), settings::menu::colors::window_bg, color_edit4_flags);
                ImGui::LabelText(xorstr("ChildBg"));        ImGui::ColorEdit4(xorstr("ChildBg"), settings::menu::colors::child_bg, color_edit4_flags);
                ImGui::LabelText(xorstr("Text"));           ImGui::ColorEdit4(xorstr("Text"), settings::menu::colors::text, color_edit4_flags);
                ImGui::LabelText(xorstr("FrameBg"));        ImGui::ColorEdit4(xorstr("FrameBg"), settings::menu::colors::frame_bg, color_edit4_flags);
                ImGui::LabelText(xorstr("FrameHoveredBg")); ImGui::ColorEdit4(xorstr("FrameHoveredBg"), settings::menu::colors::frame_hovered_bg, color_edit4_flags);
                ImGui::LabelText(xorstr("FrameActiveBg"));  ImGui::ColorEdit4(xorstr("FrameActiveBg"), settings::menu::colors::frame_active_bg, color_edit4_flags);

                ImGui::EndChild();
            }

            ImGui::SameLine();

            if (ImGui::BeginChild(xorstr("Configs"), child_size))
            {

                ImGui::EndChild();
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
        ImGui::End();
    }

    ImGui::PopStyleColor(7);
    ImGui::PopStyleVar();
}
