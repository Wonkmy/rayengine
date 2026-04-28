#include <game.h>
#include <brigeImgui.h>

int main() {
	/*Actor newGame = NewGame();
	initGame();
	RunGame(&newGame);*/
	// 实现一个GameView，然后把上面的newGame的OnDraw函数放到GameView里，类比Unity的Game视口做法
	InitWindow(GAME_WIDTH, GAME_HEIGHT, GAME_TITLE);
	rlImGuiSetup(true);
	ImGuiImpl_Init();
	while (!WindowShouldClose())
	{
		BeginDrawing();
			rlImGuiBegin();
				ImGuiImpl_CraeteDockSpace();
				ImGuiImpl_DrawText("Game", 50, 50, "Hello, ImGui!");
			rlImGuiEnd();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}