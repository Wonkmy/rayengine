#define RAYGUI_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "game.h"

void initGame() {
	// 初始化游戏相关资源
}

Font MyLoadFont()
{
	int count = 0;
	int start = 0x4E00; // 中文起始
	int end = 0x9FFF; // 中文结束

	int total = end - start + 1;
	int* codepoints = malloc(sizeof(int) * total);

	for (int i = 0; i < total; i++)
	{
		codepoints[i] = start + i;
	}

	Font font = LoadFontEx("assets/fonts/alibaba.ttf", 30, codepoints, total);

	free(codepoints);

    return font;
}

Actor NewGame() {
	Actor mainLayer;
	mainLayer.OnStart = &OnStart;
	mainLayer.OnUpdate = &OnUpdate;
	mainLayer.OnDraw = &OnDraw;
	mainLayer.OnDispose = &OnDispose;
	return mainLayer;
}
void RunGame(Actor *actor) {
	InitWindow(GAME_WIDTH, GAME_HEIGHT, GAME_TITLE);
	initGame();
	actor->OnStart();
	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(BLACK);
			actor->OnUpdate();
			actor->OnDraw();
		EndDrawing();
	}
	actor->OnDispose();
	CloseWindow();
}