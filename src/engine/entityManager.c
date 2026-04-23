#include "game.h"

Texture2D texture;
int count = 0;
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
	playerEntity = createEntity(&objects, &count, "Player1", "f1.png", (Vector2) { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f});

	playerEntity->actor.OnStart = playerEntity_OnStart;
	playerEntity->actor.OnUpdate = playerEntity_OnUpdate;
	playerEntity->actor.OnDraw = playerEntity_OnDraw;
	playerEntity->actor.OnDispose = playerEntity_OnDispose;

	camera2d.target = playerEntity->position;
}
void EntityManagerOnUpdate() {
	for (int i = 0; i < count; i++) {
		objects[i]->actor.OnUpdate();
	}
}

//if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
//	objects[0].active = 0;
//	// 移除第一个实体
//	objects[0] = (Entity){ 0 };
//}

void EntityManagerOnDraw() {

	for (int i = 0; i < count; i++)
	{
		if (!objects[i]->active) continue;
		objects[i]->actor.OnDraw();
	}
}
void EntityManagerOnGUI() {
	//ImGuiImpl_CraeteDockSpace();// 创建DockSpace
	//char finalText[100];
	//snprintf(finalText, sizeof(finalText), "X: %.1f Y: %.1f\nName: %s", entity->position.x,entity->position.y, entity->name);
	//ImGuiImpl_DrawHierarchy();
	//ImGuiImpl_DrawText("Transform", 10, 50, finalText);
	/*for (int i = 0; i < count; i++)
	{
		if (!objects[i]->active) continue;
		objects[i]->actor.OnGUI();
	}*/
}
void EntityManagerOnDispose() {
	for (int i = 0; i < count; i++) {
		if (!objects[i]->active) continue;
		objects[i]->actor.OnDispose();
		UnloadTexture(objects[i]->texture);
		objects[i] = NULL;
	}
}