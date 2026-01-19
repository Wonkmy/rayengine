//游戏主场景具体实现代码
#include "game.h"
Texture2D texture;
Vector2 pos;
Vector2 targetpos;
void MainOnStart() {
	lua_rawgeti(engine.L, LUA_REGISTRYINDEX, engine.load_ref);
	lua_pcall(engine.L, 0, 0, 0);
	pos.x = 0;
	pos.y = -0.1;
	pos = screen(pos);
	targetpos.x = 0.0f;
	targetpos.y = 0.5f;
	targetpos = screen(targetpos);
	texture = LoadTexture("test.png");
}
void MainOnUpdate() {
	lua_rawgeti(engine.L, LUA_REGISTRYINDEX, engine.update_ref);
	lua_pcall(engine.L, 0, 0, 0);
}
void MainOnDraw() {
	DrawFPS(GetScreenWidth() - 95, 10);

	lua_rawgeti(engine.L, LUA_REGISTRYINDEX, engine.draw_ref);
	lua_pcall(engine.L, 0, 0, 0);
	
	DrawTextureV(texture, pos, WHITE);
	DrawTextureV(texture, targetpos, WHITE);

	GuiButton((Rectangle) { pos.x, pos.y, 53, 50 }, "Button");

	DrawLineV(pos, targetpos, RED);
}
void MainOnDispose() {
	lua_rawgeti(engine.L, LUA_REGISTRYINDEX, engine.dispose_ref);
	lua_pcall(engine.L, 0, 0, 0);

	UnloadTexture(texture);
	lua_close(engine.L);
}