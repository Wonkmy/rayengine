#define RAYGUI_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "game.h"

void initGame() {
	// 初始化游戏相关资源
	// 初始化窗口
	InitWindow(GAME_WIDTH, GAME_HEIGHT, GAME_TITLE);
	// 设置2D相机
	camera2d.offset = WINDOW_CENTER;// 设置相机偏移为屏幕中心（注意：这里就不用再减去物体宽高的一半了）
	camera2d.rotation = GAME_ROTATE;
	camera2d.zoom = GAME_SCALE;
	SetTargetFPS(FPS);

	rlImGuiSetup(true);
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

void CameraShake(float intensity, float duration) {
	float elapsed = 0.0f;
	while (elapsed < duration) {
		float offsetX = (GetRandomValue(-100, 100) / 100.0f) * intensity;
		float offsetY = (GetRandomValue(-100, 100) / 100.0f) * intensity;
		camera2d.offset.x = WINDOW_CENTER.x + offsetX;
		camera2d.offset.y = WINDOW_CENTER.y + offsetY;
		elapsed += GetFrameTime();
	}
	camera2d.offset = WINDOW_CENTER; // 恢复相机位置
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
	actor->OnStart();
	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(BLACK);
#if defined(GAME_MODE_2D)
			BeginMode2D(camera2d);
				actor->OnUpdate();
				actor->OnDraw();
			EndMode2D();
#endif
		EndDrawing();
	}
	actor->OnDispose();
	CloseWindow();
}