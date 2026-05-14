#include "UIManager.h"
#define MINIUI_IMPLEMENTATION
#include "miniui.h"
#include <entityManager.h>
#include <game.h>

float buttonWidth = 28;
float spacing = 2;

//UIManager* UIManager::sm_pSharedUIManager = nullptr;
char name[32] = "Player";
float volume = 0.5f;
static float scroll = 0;
void UIManager::Init() {
	 _text = LoadTextureToPool(PlayerTexture, PlayerEntityTexturePath1);
}
void UIManager::Test() {
	UI_Begin();
	Rectangle screen = { 0, 0, GetScreenWidth(), GetScreenHeight() };

	// 先锚定一个面板
	Rectangle panel = AnchorRect(screen, 200, 300, 1);

	// 画面板背景
	DrawRectangleRec(panel, LIGHTGRAY);

	// 在面板内部做布局
	BeginVertical(panel.x + 10, panel.y + 10, panel.width - 20);

	Button("Option A");
	Button("Option B");

	EndLayout();
}

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