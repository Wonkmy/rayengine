//游戏主场景具体实现代码
#include "game.h"
Vector2 card_position = { 0.0f, 0.0f };	
#define CARD_WIDTH 200
#define CARD_HEIGHT 300
#define BoundingBoxWIDTH 205
#define BoundingBoxHEIGHT 305
Font font;
Texture texture;
void OnStart() {
	card_position.x = GetScreenWidth() / 2.0f - (CARD_WIDTH / 2);
	card_position.y = GetScreenHeight() / 2.0f - (CARD_HEIGHT / 2);
	EntityOnStart();
	font = MyLoadFont();
}
void OnUpdate() {
	EntityOnUpdate();
	if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		if (GetMouseX() >= card_position.x && GetMouseX() <= card_position.x + CARD_WIDTH &&
			GetMouseY() >= card_position.y && GetMouseY() <= card_position.y + CARD_HEIGHT) {
			card_position.x = GetMouseX() - (CARD_WIDTH / 2);
			card_position.y = GetMouseY() - (CARD_HEIGHT / 2);
		}
	}
}
void OnDraw() {
	EntityOnDraw();
	/*BoundingBox card_box = { {card_position.x, card_position.y}, {card_position.x + BoundingBoxWIDTH, card_position.y + BoundingBoxHEIGHT} };
	DrawBoundingBox(card_box, RED);
	
	BoundingBox card_box2 = { {0,0}, {100,100} };
	DrawBoundingBox(card_box2, GREEN);
	DrawRectangle(card_position.x, card_position.y, CARD_WIDTH, CARD_HEIGHT, DARKBLUE);
	
	DrawTextEx(font, u8"好的", card_position, 30, 2, WHITE);

	if(CheckCollisionBoxes(card_box, card_box2)) {
		DrawText("IsHited!!", 10, 10, 20, YELLOW);
	}*/
}
void OnDispose() {
	EntityOnDispose();
}