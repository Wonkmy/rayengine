#ifndef GAME_H
#define GAME_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "mainlayer.h"
#include "rlImGui.h"
#include "rlgl.h"
#include <string.h>
#include "lualib.h"
#include "lauxlib.h"
#include "raygui.h"

#define REG_API extern
#define RAYLIB_ENGINE_EXPORT REG_API


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
#define GAME_WIDTH 1920.0f
#define GAME_HEIGHT 1080.0f
#define GAME_SCALE 0.5f
#define GAME_ROTATE 0.0f
#define GAME_TITLE "RayEditor-v0.0.1"
#define GAME_BACKGROUND_COLOR BLACK
#define GAME_ASSETS_ROOT_PATH "assets/"// 游戏资源根目录

// Camera相关
#define CAMERA_ZOOM 1.0f

// 窗口相关
#define WINDOW_CENTER Vector2{ GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f }

void initGame();
Font MyLoadFont();

RAYLIB_ENGINE_EXPORT Camera2D camera2d;

void CameraShake(float intensity, float duration);

// 工具函数定义
Vector2 rotate_vector(Vector2 v, Vector2 center, double angle_deg);
void rotate_points_batch(Vector2 points[], int count, Vector2 center, double angle_deg);
int GetIniInt(const char* filePath, const char* targetKey, int defaultValue);

#endif // GAME_H