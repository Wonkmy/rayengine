#include "UIManager.h"

float buttonWidth = 28;
float spacing = 2;

UIManager* UIManager::sm_pSharedUIManager = nullptr;

void UIManager:: CreatePanel() {
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::Begin("MenuBar", NULL, window_flags);
	// 当前窗口宽度
	float windowWidth = ImGui::GetContentRegionAvail().x;
	// 总宽度 = 3个按钮 + 2个间距
	float totalWidth = buttonWidth * 3 + spacing * 2;
	// 起始X（居中）
	float startX = (windowWidth - totalWidth) * 0.5f;
	ImGui::SetCursorPosX(startX);
	ImGui::Button("Play", ImVec2(28, 15));
	ImGui::SameLine(0, 2);
	ImGui::Button("Stop", ImVec2(28, 15));
	ImGui::SameLine(0, 2);
	ImGui::Button("Step>>", ImVec2(28, 15));
	ImGui::End();
}