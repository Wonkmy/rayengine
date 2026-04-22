//#include "raylib.h"
#include "raygui.h"
#include <stdint.h>
#include "lualib.h"
#include "math.h"
#include "mainlayer.h"
#include "MeshRender.h"
#include <stdio.h>
#include "rlImGui.h"

typedef struct Actor {
	void(*OnStart)();
	void(*OnUpdate)();
	void(*OnDraw)();
	void(*OnDispose)();
	void(*OnGUI)();
} Actor;


typedef struct Entity {
	char* name;
	Vector2 position;
	Texture2D texture;
	BoundingBox boundingBox;
} Entity;

void EntityOnStart();
void EntityOnUpdate();
void EntityOnDraw();
void EntityOnGUI();
void EntityOnDispose();

// GAME 相关
#define GAME_MODE_2D
#define FPS 120.0f
#define GAME_WIDTH 1280.0f
#define GAME_HEIGHT 720.0f
#define GAME_SCALE 0.25f
#define GAME_ROTATE 0.0f
#define GAME_TITLE "MyGames"

// Camera相关
#define CAMERA_ZOOM 1.0f

// 窗口相关
#define WINDOW_CENTER (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }
//#define WINDOW_CENTER (Vector2){0.0f,0.0f }

void initGame();
Actor NewGame();
void RunGame(Actor *actor);
Font MyLoadFont();

Camera2D camera2d;

void CameraShake(float intensity, float duration);
extern void ImGuiImpl_DrawText(const char* name, int p_x, int p_y, const char* fmt,...);
