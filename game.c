#define RAYGUI_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "raylib.h"
#include "game.h"
// 游戏主渲染、更新循环实现文件
int createGameApp(GameEngine *engine,int width, int height, const char *title)
{
	InitWindow(width, height, title);
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

int createPNG(char const* filename, int x, int y, int comp, const void* data) {
	int ok = stbi_write_png(filename, x, y, 4, data, 2 * sizeof(uint32_t));
	return ok;
}