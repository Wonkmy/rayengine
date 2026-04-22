//游戏主场景具体实现代码
#include "game.h"
Vector2 card_position = { 0.0f, 0.0f };	
#define CARD_WIDTH 200
#define CARD_HEIGHT 300
#define BoundingBoxWIDTH 205
#define BoundingBoxHEIGHT 305
//Font font;
Texture texture;
void OnStart() {
	card_position.x = GetScreenWidth() / 2.0f - (CARD_WIDTH / 2);
	card_position.y = GetScreenHeight() / 2.0f - (CARD_HEIGHT / 2);
	EntityOnStart();
	//font = MyLoadFont();
}
void OnUpdate() {
	EntityOnUpdate();
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		if (GetMouseX() >= card_position.x && GetMouseX() <= card_position.x + CARD_WIDTH &&
			GetMouseY() >= card_position.y && GetMouseY() <= card_position.y + CARD_HEIGHT) {
			card_position.x = GetMouseX() - (CARD_WIDTH / 2);
			card_position.y = GetMouseY() - (CARD_HEIGHT / 2);
		}
	}
}
void OnDraw() {
	EntityOnDraw();
}
void OnGUI() {
	EntityOnGUI();
}
void OnDispose() {
	EntityOnDispose();
}