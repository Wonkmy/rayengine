#include <game.h>
#include "UIManager.h"
#include "brigeImgui.h"
#include <imgui_internal.h>
// 当前editor项目只做两件事：
// 1 通过engine那边提供的接口，启动游戏
// 2 必要时做一些调试性的窗口，基于imgui库

bool runGame = false;
bool singleRun = false;

int main() {
	Actor mainLayer = NewGame();
	initGame();
	UIManager* sm_pSharedUIManager = new UIManager();
	rlImGuiSetup(true);
	ImGuiImpl_Init();
	
	mainLayer.OnStart();
	
	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(BLACK);
			if (runGame) {
				RunGame(&mainLayer);
			}
			
			if (runGame == false) {
				rlImGuiBegin();
					ImGuiImpl_CraeteDockSpace();
					sm_pSharedUIManager->CreatePanel();
				rlImGuiEnd();
			}
			
		EndDrawing();
	}
	mainLayer.OnDispose();
	runGame = false;
	CloseWindow();
	return 0;
}