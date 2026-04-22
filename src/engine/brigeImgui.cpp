extern "C" {
#include "raylib.h"
#include "rlImGui.h"
#include "game.h"
}

#include "imgui.h"

extern "C" void ImGuiImpl_DrawText(const char* name,int p_x,int p_y, const char* fmt,...)
{
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Always);
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::Begin(name);
    ImGui::SetCursorPos(ImVec2(p_x, p_y));
    ImGui::Text(fmt);
    ImGui::End();
}