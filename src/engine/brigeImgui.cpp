extern "C" {
#include "raylib.h"
#include "rlImGui.h"
}

#include "imgui.h"

extern "C" void ImGui_Draw()
{
    ImGui::Begin("Test Window");
    ImGui::SetCursorPos(ImVec2(100, 100));
    ImGui::Text("Hello from ImGui!");
    ImGui::End();
}