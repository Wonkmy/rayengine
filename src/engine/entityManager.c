#include "game.h"
Texture2D texture;
Entity* allEntitys = NULL;
int counts = 0;

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
	playerEntity = createEntity(&allEntitys, &counts, "Player1", "f1.png",(Vector2) { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f});

	playerEntity->actor.OnStart = playerEntity_OnStart;
	playerEntity->actor.OnUpdate = playerEntity_OnUpdate;
	playerEntity->actor.OnDraw = playerEntity_OnDraw;
	playerEntity->actor.OnDispose = playerEntity_OnDispose;

	camera2d.target = playerEntity->position;

	enemyEntity = createEntity(&allEntitys, &counts, "Enemy1", "f2.png", (Vector2) { GetScreenWidth() / 2.0f + 100, GetScreenHeight() / 2.0f });

	enemyEntity->actor.OnStart = enemyEntity_OnStart;
	enemyEntity->actor.OnUpdate = enemyEntity_OnUpdate;
	enemyEntity->actor.OnDraw = enemyEntity_OnDraw;
	enemyEntity->actor.OnDispose = enemyEntity_OnDispose;
	
}
void EntityManagerOnUpdate() {
	for (int i = 0; i < counts; i++) {
		if (!allEntitys[i].active) continue;
		allEntitys[i].actor.OnUpdate();
	}
}

void EntityManagerOnDraw() {

	for (int i = 0; i < counts; i++)
	{
		if (!allEntitys[i].active) continue;
		allEntitys[i].actor.OnDraw();
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
	for (int i = 0; i < counts; i++) {
		if (!allEntitys[i].active) continue;
		allEntitys[i].actor.OnDispose();
		UnloadTexture(allEntitys[i].texture);
	}
}