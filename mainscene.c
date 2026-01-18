#include "mainlayer.h" // 游戏主场景
// 游戏逻辑实现文件
void load()
{
	// Game initialization logic here
	MainOnStart();
}
void update() {
	// Game update logic here
	MainOnUpdate();
}
void draw()
{
	// Game drawing logic here
	MainOnDraw();
}

void dispose() {
	MainOnDispose();
}