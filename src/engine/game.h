//#include "raylib.h"
#include "raygui.h"
#include <stdint.h>
#include "lualib.h"
#include "math.h"
#include "mainlayer.h"
#include "MeshRender.h"
#include <stdio.h>
#include "rlImGui.h"
#include "gamefuncs.h"


void DrawNode(int index);

typedef struct Actor {
	void(*OnStart)();
	void(*OnUpdate)();
	void(*OnDraw)();
	void(*OnDispose)();
	void(*OnGUI)();
} Actor;


typedef struct Entity {
	char* name;
	bool active;
	Vector2 position;
	Texture2D texture;
	BoundingBox boundingBox;
	bool drawBoundingBox;
	Actor actor;
} Entity;


Entity* createEntity(struct Entity** arr, int* count, const char* name, const char* texturePath, Vector2 position);
void UpdateBoundingBox(Entity* entity);
void EntityManagerOnStart();
void EntityManagerOnUpdate();
void EntityManagerOnDraw();
void EntityManagerOnGUI();
void EntityManagerOnDispose();

// GAME 相关
#define GAME_MODE_2D
#define FPS 120.0f
#define GAME_WIDTH 1280.0f
#define GAME_HEIGHT 720.0f
#define GAME_SCALE 0.25f
#define GAME_ROTATE 0.0f
#define GAME_TITLE "MyGames"
#define GAME_BACKGROUND_COLOR BLACK

// Entity相关
#define MAX_ENTITYS 100
Entity* objects[MAX_ENTITYS];
Entity* playerEntity;// 玩家实体
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
extern void ImGuiImpl_Init();
extern void ImGuiImpl_DrawText(const char* name, int p_x, int p_y, const char* fmt,...);
extern void ImGuiImpl_CraeteDockSpace();
extern void ImGuiImpl_DrawHierarchy();
