#include "raylib.h"
#include "raygui.h"
#include <stdint.h>
#include "lualib.h"
#include "math.h"
#include "mainlayer.h"
#include "MeshRender.h"

typedef struct Actor {
	void(*OnStart)();
	void(*OnUpdate)();
	void(*OnDraw)();
	void(*OnDispose)();
} Actor;


typedef struct Entity {
	Vector2 position;
	Texture2D texture;
	BoundingBox boundingBox;
} Entity;

void EntityOnStart();
void EntityOnUpdate();
void EntityOnDraw();
void EntityOnDispose();

#define FPS 60.0f
#define GAME_WIDTH 1280.0f
#define GAME_HEIGHT 720.0f
#define GAME_TITLE "MyGames"

Actor NewGame();
void RunGame(Actor *actor);
Font MyLoadFont();