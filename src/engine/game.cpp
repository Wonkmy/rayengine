#define RAYGUI_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "game.h"
#include "brigeImgui.h"
Camera2D camera2d;
void initGame() {
	// 初始化游戏相关资源
	// 初始化窗口
	InitWindow(GAME_WIDTH, GAME_HEIGHT, GAME_TITLE);
	// 设置2D相机
	camera2d.offset = WINDOW_CENTER;// 设置相机偏移为屏幕中心（注意：这里就不用再减去物体宽高的一半了）
	camera2d.rotation = GAME_ROTATE;
	camera2d.zoom = CAMERA_ZOOM;
	SetTargetFPS(FPS);
}

Font MyLoadFont()
{
	int count = 0;
	int start = 0x4E00; // 中文起始
	int end = 0x9FFF; // 中文结束

	int total = end - start + 1;
	int* codepoints = (int*)malloc(sizeof(int) * total);

	for (int i = 0; i < total; i++)
	{
		codepoints[i] = start + i;
	}

	Font font = LoadFontEx("assets/fonts/alibaba.ttf", 30, codepoints, total);

	free(codepoints);

    return font;
}

int GetIniInt(const char* filePath, const char* targetKey, int defaultValue)
{
	char* content = LoadFileText(filePath);
	if (!content)
	{
		printf("Failed to load file: %s\n", filePath);
		return defaultValue;
	}

	int result = defaultValue;

	char* line = strtok(content, "\n");
	while (line != NULL)
	{
		char* equal = strchr(line, '=');
		if (equal)
		{
			*equal = '\0';

			char* key = line;
			char* value = equal + 1;

			// 去掉 key 前空格
			while (*key == ' ') key++;

			// 去掉 key 末尾空格
			char* keyEnd = key + strlen(key) - 1;
			while (keyEnd > key && *keyEnd == ' ')
			{
				*keyEnd = '\0';
				keyEnd--;
			}

			// 去掉 value 前空格
			while (*value == ' ') value++;

			// 去掉 value 末尾的 \r 或空格
			char* valueEnd = value + strlen(value) - 1;
			while (valueEnd > value && (*valueEnd == ' ' || *valueEnd == '\r'))
			{
				*valueEnd = '\0';
				valueEnd--;
			}

			// 匹配 key
			if (strcmp(key, targetKey) == 0)
			{
				result = atoi(value);
				break;
			}
		}

		line = strtok(NULL, "\n");
	}

	UnloadFileText(content);
	return result;
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
	mainLayer.OnGUI = &OnGUI;
	mainLayer.OnDispose = &OnDispose;
	return mainLayer;
}
void RunGame(Actor *actor) {
	actor->OnUpdate();
	BeginMode2D(camera2d);// 开始2D模式
	actor->OnDraw();
	EndMode2D();// 这里会增加一次DrawCall
	DrawText(TextFormat("DrawCalls: %d", rlGetDrawCallCounter()), 10, 40, 20, GREEN);
	DrawFPS(GetScreenWidth() - 100, 10);
}