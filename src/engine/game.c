#define RAYGUI_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
#include "raylib.h"
#include "game.h"
#include "../3rdlib/raygui-4.0/styles/jungle/style_jungle.h"
// 游戏主渲染、更新循环实现文件
int createGameApp(GameEngine *engine,int width, int height, const char *title)
{
	InitWindow(width, height, title);
	Vector2 pos = GetMonitorPosition(1);
	SetWindowPosition(pos.x + 20, pos.y + 40);
	engine->load();
	while (!WindowShouldClose())
	{
		engine-> update();
		BeginDrawing();
		ClearBackground(BLACK);
		engine->draw();
		EndDrawing();
	}
	engine->dispose();
	// 释放engine
	engine = NULL;
	CloseWindow();
	return 0;
}