#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "raygui.h"
#include <stdint.h>
#include "lualib.h"
#define FPS 60.0f
#define GAME_WIDTH 1280.0f
#define GAME_HEIGHT 720.0f

#ifndef GAMEENGINE_DEFINED
#define GAMEENGINE_DEFINED
typedef struct GameEngine {
	lua_State* L;
	void (*load)();
	void (*update)();
	void (*draw)();
	void (*dispose)();
	int16_t load_ref;
	int16_t update_ref;
	int16_t draw_ref;
	int16_t dispose_ref;
} GameEngine;
#endif

GameEngine engine;
Vector3 translate_z(Vector3 v, float dz);
Vector3 rotate_xz(Vector3 v, float angle);
Vector2 project(Vector3 v);
Vector2 screen(Vector2 p);
void frame(float dz);
void load();
void update();
void draw();
void dispose();
int createPNG(char const* filename, int x, int y, int comp, const void* data);
int createGameApp(GameEngine *engine,int width, int height, const char* title);
void Draw3D( float dz);
#endif // GAME_H