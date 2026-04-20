//游戏主场景具体实现代码
#include "game.h"
#ifdef USE_LUA


Vector2 p;
Vector2 pos;
bool showMessageBox = false;
void MainOnStart() {
	p.x = 0;
	p.y = 0;
	pos = screen(p);

	lua_rawgeti(engine.L, LUA_REGISTRYINDEX, engine.load_ref);
	lua_pcall(engine.L, 0, 0, 0);
}
void MainOnUpdate() {
	lua_rawgeti(engine.L, LUA_REGISTRYINDEX, engine.update_ref);
	lua_pcall(engine.L, 0, 0, 0);
}
void MainOnDraw() {
	DrawFPS(GetScreenWidth() - 95, 10);
	lua_rawgeti(engine.L, LUA_REGISTRYINDEX, engine.draw_ref);
	lua_pcall(engine.L, 0, 0, 0);
	if (GuiButton((Rectangle) { screen(p).x, screen(p).y, 120, 30 }, "#191#Show Message")) showMessageBox = true;

	if (showMessageBox)
	{
		int result = GuiMessageBox((Rectangle) { 85, 70, 250, 100 },
			"#191#Message Box", "Hi! This is a message!", "Nice;Cool");

		if (result >= 0) showMessageBox = false;
	}
}
void MainOnDispose() {
	lua_rawgeti(engine.L, LUA_REGISTRYINDEX, engine.dispose_ref);
	lua_pcall(engine.L, 0, 0, 0);

	lua_close(engine.L);
}
#endif // USE_LUA

Texture texture;

void MainOnStart() {
	texture = LoadTexture("assets/sprites/test.png");
}
void MainOnUpdate() {
	
}
void MainOnDraw() {
	DrawTexture(texture, 0, 0, WHITE);
}
void MainOnDispose() {
}