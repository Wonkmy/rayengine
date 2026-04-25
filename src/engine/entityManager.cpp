#include "PlayerEntity.h"
std::vector<std::unique_ptr<Entity>> entitys;
void EntityManagerOnStart() {
	std::string playerName = "Player1";
	const char* playerTexturePath = "assets/sprites/f1.png";
	PlayerEntity* playerEntity = new PlayerEntity();
	playerEntity->name = playerName;
	playerEntity->texture = LoadTexture(playerTexturePath);
	playerEntity->OnStart();
	//entitys.emplace_back(playerEntity);
	entitys.emplace_back(std::make_unique<PlayerEntity>());
}
void EntityManagerOnUpdate() {
    for (int i = 0; i < entitys.size(); i++) {
        if (entitys[i]->active) {
            entitys[i]->OnUpdate();
        }
    }
}

void EntityManagerOnDraw() {
    for (int i = 0; i < entitys.size(); i++) {
        if (entitys[i]->active) {
            entitys[i]->OnDraw();
        }
    }
}
void EntityManagerOnGUI() {
    for (int i = 0; i < entitys.size(); i++) {
        if (entitys[i]->active) {
            entitys[i]->OnGUI();
        }
    }
//	//ImGuiImpl_CraeteDockSpace();// 创建DockSpace
//	//char finalText[100];
//	//snprintf(finalText, sizeof(finalText), "X: %.1f Y: %.1f\nName: %s", entity->position.x,entity->position.y, entity->name);
//	//ImGuiImpl_DrawHierarchy();
//	//ImGuiImpl_DrawText("Transform", 10, 50, "finalText");
//	/*for (int i = 0; i < count; i++)
//	{
//		if (!objects[i]->active) continue;
//		objects[i]->actor.OnGUI();
//	}*/
//	//ImGuiImpl_DrawSceneView();
}
void EntityManagerOnDispose() {
    for (int i = 0; i < entitys.size(); ) {
        if (entitys[i]->active) {
            entitys[i]->OnDispose();
        }
    }
}

// **************************工具函数**************************
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define DEG_TO_RAD(deg) ((deg) * M_PI / 180.0)

// 单个点旋转函数
Vector2 rotate_vector(Vector2 v, Vector2 center, double angle_deg) {
	double rad = DEG_TO_RAD(angle_deg);
	double cos_a = cos(rad);
	double sin_a = sin(rad);
	double dx = v.x - center.x;
	double dy = v.y - center.y;
	Vector2 result;
	result.x = center.x + dx * cos_a - dy * sin_a;
	result.y = center.y + dx * sin_a + dy * cos_a;
	return result;
}

// 批量旋转多个点
void rotate_points_batch(Vector2 points[], int count, Vector2 center, double angle_deg) {
	for (int i = 0; i < count; i++)
	{
		points[i] = rotate_vector(points[i], center, angle_deg);
	}
}

void RotateBoundingBox(Entity* _entity, float angle) {
	Vector2 rectangle[] = {
		{_entity->position.x - _entity->texture.width * 0.5f * GAME_SCALE, _entity->position.y + _entity->texture.height * 0.5f * GAME_SCALE},  // 左下
		{_entity->position.x + _entity->texture.width * 0.5f * GAME_SCALE,  _entity->position.y + _entity->texture.height * 0.5f * GAME_SCALE},  // 右下
		{_entity->position.x + _entity->texture.width * 0.5f * GAME_SCALE,_entity->position.y - _entity->texture.height * 0.5f * GAME_SCALE},  // 右上
		{_entity->position.x - _entity->texture.width * 0.5f * GAME_SCALE, _entity->position.y - _entity->texture.height * 0.5f * GAME_SCALE}   // 左上
	};
	int n = sizeof(rectangle) / sizeof(rectangle[0]);
	rotate_points_batch(rectangle, n, Vector2{ _entity->position.x, _entity->position.y }, angle);

	float minX = rectangle[0].x;
	float minY = rectangle[0].y;
	float maxX = rectangle[0].x;
	float maxY = rectangle[0].y;

	for (int i = 1; i < n; i++)
	{
		if (rectangle[i].x < minX) minX = rectangle[i].x;
		if (rectangle[i].y < minY) minY = rectangle[i].y;
		if (rectangle[i].x > maxX) maxX = rectangle[i].x;
		if (rectangle[i].y > maxY) maxY = rectangle[i].y;
	}
	_entity->boundingBox = BoundingBox{ Vector3{minX, minY, 0},
Vector3 {
maxX, maxY, 0
}
	};
}