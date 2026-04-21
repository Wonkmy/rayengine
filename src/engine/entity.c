#include "game.h"
Entity entity;

float scale = 0.25f; // 调整缩放比例以适应屏幕

void lerp(Vector2* start, Vector2* end, float t, Vector2* result) {
	result->x = start->x + (end->x - start->x) * t;
	result->y = start->y + (end->y - start->y) * t;
}

void updateNewPosition(Vector2* currentPosition, Vector2* targetPosition, float deltaTime) {
	float speed = 5.0f; // 调整速度
	Vector2 newPosition;
	lerp(currentPosition, targetPosition, speed * deltaTime, &newPosition);
	currentPosition->x = newPosition.x * scale;
	currentPosition->y = newPosition.y * scale;
	entity.boundingBox.min.x = currentPosition->x * scale;
	entity.boundingBox.min.y = currentPosition->y * scale;
	entity.boundingBox.max.x = currentPosition->x * scale;
	entity.boundingBox.max.y = currentPosition->y * scale;
}

void EntityOnStart() {
	entity.position = (Vector2){ 0.0f, 0.0f };
	entity.texture = LoadTexture("assets/sprites/f1.png");
	entity.position.x = (GetScreenWidth() / 2.0f - (entity.texture.width / 2));
	entity.position.y = (GetScreenHeight() / 2.0f - (entity.texture.height / 2));
	entity.boundingBox = (BoundingBox){ {entity.position.x , entity.position.y}, {entity.position.x + entity.texture.width * scale,entity.position.y + entity.texture.height * scale}};
}
void EntityOnUpdate() {
	//updateNewPosition(&entity.position, &(Vector2){GetMouseX() - entity.texture.width / 2, GetScreenHeight() - entity.texture.height / 2 }, GetFrameTime());
}
void EntityOnDraw() {
	DrawTextureEx(entity.texture, entity.position, 0.0f, scale, WHITE);
	//DrawTexture(entity.texture, entity.position.x, entity.position.y, WHITE);
	DrawBoundingBox(entity.boundingBox, RED);
}
void EntityOnDispose() {
	UnloadTexture(entity.texture);
	entity = (Entity){ 0 };
}