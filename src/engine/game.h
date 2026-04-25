#ifndef GAME_H
#define GAME_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "mainlayer.h"
#include "rlImGui.h"
#include "rlgl.h"
using namespace std;

#define REG_API extern


typedef struct Actor {
	void(*OnStart)();
	void(*OnUpdate)();
	void(*OnDraw)();
	void(*OnDispose)();
	void(*OnGUI)();
} Actor;

Actor NewGame();
void RunGame(Actor* actor);
// GAME 相关
#define GAME_MODE_2D
#define FPS 120.0f
#define GAME_WIDTH 1280.0f
#define GAME_HEIGHT 720.0f
#define GAME_SCALE 0.25f
#define GAME_ROTATE 0.0f
#define GAME_TITLE "MyGames"
#define GAME_BACKGROUND_COLOR BLACK
#define GAME_ASSETS_ROOT_PATH "assets/"// 游戏资源根目录

// Camera相关
#define CAMERA_ZOOM 1.0f

// 窗口相关
#define WINDOW_CENTER Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }

void initGame();
Font MyLoadFont();

REG_API Camera2D camera2d;

void CameraShake(float intensity, float duration);
REG_API void ImGuiImpl_Init();
REG_API void ImGuiImpl_DrawText(const char* name, int p_x, int p_y, const char* fmt,...);
REG_API void ImGuiImpl_CraeteDockSpace();
REG_API void ImGuiImpl_DrawHierarchy();// 绘制层级面板
REG_API void ImGuiImpl_DrawSceneView();// 绘制场景面板
REG_API void ImGuiImpl_DrawGameView();// 绘制检查器面板

// 工具函数定义
Vector2 rotate_vector(Vector2 v, Vector2 center, double angle_deg);
void rotate_points_batch(Vector2 points[], int count, Vector2 center, double angle_deg);

#endif // GAME_H