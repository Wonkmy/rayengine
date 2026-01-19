//游戏主场景具体实现代码
#include "game.h"
#include "Player.h"

Player player;

void MainOnStart() {
	player_Init(&player);
	player.init(&player);

	player.X = 100;
	player.Y = 150;

	lua_rawgeti(engine.L, LUA_REGISTRYINDEX, engine.load_ref);
	lua_pcall(engine.L, 0, 0, 0);
}
void MainOnUpdate() {
	lua_rawgeti(engine.L, LUA_REGISTRYINDEX, engine.update_ref);
	lua_pcall(engine.L, 0, 0, 0);
}
void MainOnDraw() {
	DrawFPS(GetScreenWidth() - 95, 10);
	player_Draw(&player);
	lua_rawgeti(engine.L, LUA_REGISTRYINDEX, engine.draw_ref);
	lua_pcall(engine.L, 0, 0, 0);
}
void MainOnDispose() {
	lua_rawgeti(engine.L, LUA_REGISTRYINDEX, engine.dispose_ref);
	lua_pcall(engine.L, 0, 0, 0);
	lua_close(engine.L);
}