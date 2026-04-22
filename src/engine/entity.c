#include "game.h"
Entity entity;
Texture2D texture;
void lerp(Vector2* start, Vector2* end, float t, Vector2* result) {
	result->x = start->x + (end->x - start->x) * t;
	result->y = start->y + (end->y - start->y) * t;
}

void UpdateBoundingBox() {
	Vector3 min = (Vector3){ entity.position.x - entity.texture.width / 2 * GAME_SCALE, entity.position.y - entity.texture.height / 2 * GAME_SCALE };
	Vector3 max = (Vector3){ entity.position.x + entity.texture.width / 2 * GAME_SCALE,  entity.position.y + entity.texture.height / 2 * GAME_SCALE };
	entity.boundingBox = (BoundingBox){ min, max };
}

void updateNewPosition(Vector2* currentPosition, Vector2* targetPosition) {
	currentPosition->x = targetPosition->x;
	currentPosition->y = targetPosition->y;
}

void EntityOnStart() {
	entity.name = "Player1"; // 初始化名称为空字符串
	entity.position = (Vector2){ 0.0f, 0.0f };
	entity.texture = LoadTexture("assets/sprites/f1.png");
	entity.position.x = (GetScreenWidth() / 2.0f);
	entity.position.y = (GetScreenHeight() / 2.0f);
	entity.boundingBox = (BoundingBox){ entity.position.x + entity.texture.width * GAME_SCALE,  entity.position.y + entity.texture.height * GAME_SCALE };

	camera2d.target = entity.position;
}
void EntityOnUpdate() {
	entity.position.x = GetMouseX();
	entity.position.y = GetMouseY();
	UpdateBoundingBox();
}
void EntityOnDraw() {
	DrawTexturePro(entity.texture,
		(Rectangle) {
		0,0, entity.texture.width, entity.texture.height
	},
		(Rectangle) {
		entity.position.x, entity.position.y, entity.texture.width* GAME_SCALE, entity.texture.height* GAME_SCALE
	},
		(Vector2) {
		entity.texture.width / 2 * GAME_SCALE, entity.texture.height / 2 * GAME_SCALE
	},
		0.0f, WHITE);

	DrawBoundingBox(entity.boundingBox, RED);
}
void EntityOnGUI() {
	char finalText[100];
	snprintf(finalText, sizeof(finalText), "X: %.1f Y: %.1f\nName: %s", entity.position.x,entity.position.y, entity.name);
	ImGuiImpl_DrawText("Transform", 10, 50, finalText);
	DrawFPS(GetScreenWidth() - 100, 10);
}
void EntityOnDispose() {
	UnloadTexture(entity.texture);
	entity = (Entity){ 0 };
}