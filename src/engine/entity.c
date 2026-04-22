#include "game.h"
Entity entity;
Texture2D texture;
void lerp(Vector2* start, Vector2* end, float t, Vector2* result) {
	result->x = start->x + (end->x - start->x) * t;
	result->y = start->y + (end->y - start->y) * t;
}

void UpdateBoundingBox() {
	Vector3 min = (Vector3){ entity.position.x, entity.position.y };
	Vector3 max = (Vector3){ entity.position.x + entity.texture.width,  entity.position.y + entity.texture.height};
	entity.boundingBox = (BoundingBox){ min, max };
}

void updateNewPosition(Vector2* currentPosition, Vector2* targetPosition) {
	currentPosition->x = targetPosition->x;
	currentPosition->y = targetPosition->y;
}

void EntityOnStart() {
	entity.position = (Vector2){ 0.0f, 0.0f };
	entity.texture = LoadTexture("assets/sprites/f1.png");
	entity.position.x = (GetScreenWidth() / 2.0f - (entity.texture.width / 2));
	entity.position.y = (GetScreenHeight() / 2.0f - (entity.texture.height / 2));
	entity.boundingBox = (BoundingBox){ entity.position.x + entity.texture.width,  entity.position.y + entity.texture.height };

	camera2d.target = entity.position;
}
void EntityOnUpdate() {
	//updateNewPosition(&entity.position, &(Vector2){GetMouseX() - entity.texture.width / 2, entity.position.y });
	entity.position.x = GetMouseX() / GAME_SCALE - entity.texture.width / 4.0f;
	entity.position.y = GetScreenHeight() - entity.texture.height / 2.0f;
	UpdateBoundingBox();
}
void EntityOnDraw() {
	//DrawTexturePro(entity.texture,
	//	(Rectangle) {
	//	0, 0, entity.texture.width, entity.texture.height
	//}, // 源矩形（纹理坐标）
	//	(Rectangle) {
	//	entity.position.x, entity.position.y, entity.texture.width, entity.texture.height
	//}, // 目标矩形（屏幕坐标）
	//	(Vector2) {
	//	0.0f, 0.0f
	//},// 设置原点（旋转和缩放的中心点）
	//	0.0f, WHITE);

	//DrawBoundingBox(entity.boundingBox, RED);


	//// ===== ImGui 开始 =====

	rlImGuiBegin();
	ImGui_Draw();
	rlImGuiEnd();
	//// ===== ImGui 结束 =====
}
void EntityOnDispose() {
	UnloadTexture(entity.texture);
	entity = (Entity){ 0 };
}