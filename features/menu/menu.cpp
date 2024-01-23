#include "menu.h"

void menu::render() noexcept
{
    using namespace ImGui;

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
            EndChild();
        }

        SameLine();

        if (BeginChild(xorstr("Accuracy"), child_size))
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

            EndChild();
        }

        SameLine();

        if (BeginChild(xorstr("Configs"), child_size))
        {

            EndChild();
        }

        EndTabItem();
    }

    EndTabBar();
    End();

    PopStyleColor(7);
    PopStyleVar();
}
