#include "game.h"
Entity* entity;
Texture2D texture;
void lerp(Vector2* start, Vector2* end, float t, Vector2* result) {
	result->x = start->x + (end->x - start->x) * t;
	result->y = start->y + (end->y - start->y) * t;
}

void UpdateBoundingBox(Entity* entity) {
	Vector3 min = (Vector3){ entity->position.x - entity->texture.width / 2 * GAME_SCALE, entity->position.y - entity->texture.height / 2 * GAME_SCALE };
	Vector3 max = (Vector3){ entity->position.x + entity->texture.width / 2 * GAME_SCALE,  entity->position.y + entity->texture.height / 2 * GAME_SCALE };
	entity->boundingBox = (BoundingBox){ min, max };
}

void updateNewPosition(Vector2* currentPosition, Vector2* targetPosition) {
	currentPosition->x = targetPosition->x;
	currentPosition->y = targetPosition->y;
}

void EntityManagerOnStart() {
	entity = createEntity("Player1", "f1.png", (Vector2) { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f});
	camera2d.target = entity->position;
}
void EntityManagerOnUpdate() {
	for (int i = 0; i < MAX_ENTITYS; i++) {
		if (!objects[i].active) continue;
		objects[i].position.x = GetMouseX();
		objects[i].position.y = GetMouseY();
		UpdateBoundingBox(&objects[i]);
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		objects[0].active = 0;
		// 移除第一个实体
		objects[0] = (Entity){ 0 };
	}
}
void EntityManagerOnDraw() {

	for (int i = 0; i < MAX_ENTITYS; i++)
	{
		if (!objects[i].active) continue;
		DrawTexturePro(objects[i].texture,
			(Rectangle){0,0, objects[i].texture.width, objects[i].texture.height},
			(Rectangle){objects[i].position.x, objects[i].position.y, objects[i].texture.width* GAME_SCALE, objects[i].texture.height* GAME_SCALE},
			(Vector2){objects[i].texture.width / 2 * GAME_SCALE, objects[i].texture.height / 2 * GAME_SCALE},
			0.0f, WHITE);

		if (objects[i].drawBoundingBox) {
			DrawBoundingBox(objects[i].boundingBox, RED);
		}
	}
}
void EntityManagerOnGUI() {
	//ImGuiImpl_CraeteDockSpace();// 创建DockSpace
	//char finalText[100];
	//snprintf(finalText, sizeof(finalText), "X: %.1f Y: %.1f\nName: %s", entity->position.x,entity->position.y, entity->name);
	//ImGuiImpl_DrawHierarchy();
	//ImGuiImpl_DrawText("Transform", 10, 50, finalText);
}
void EntityManagerOnDispose() {
	for (int i = 0; i < MAX_ENTITYS; i++) {
		if (!objects[i].active) continue;
		UnloadTexture(objects[i].texture);
		objects[i] = (Entity){ 0 };
	}
}