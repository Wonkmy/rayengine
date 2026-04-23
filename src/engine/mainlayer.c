//游戏主场景具体实现代码
#include "game.h"
void OnStart() {
	EntityManagerOnStart();
}
void OnUpdate() {
	EntityManagerOnUpdate();
}
void OnDraw() {
	EntityManagerOnDraw();
}
void OnGUI() {
	EntityManagerOnGUI();
	DrawFPS(GetScreenWidth() - 100, 10);
}
void OnDispose() {
	EntityManagerOnDispose();
}