#include "game.h"

// ==========================玩家相关函数实现=========================
//float rotationAngle = 0.0f;
//bool needSort = false;
//bool Attacking = false;
//float bulletSpeed = 2.0f;
//int entityId = 0;
//void playerEntity_OnStart() {
//	//playerEntity->drawBoundingBox = true;
//}
//void playerEntity_OnUpdate() {
//	playerEntity->position.x = GetMouseX();
//	playerEntity->position.y = GetMouseY();
//	
//	UpdateBoundingBox(playerEntity);
//	//rotationAngle += 1.0f; // 每帧增加1度
//
//	/*Entity* player = findEntityByName("Player1");
//	if (player && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
//		player->zIndex = 2;
//		needSort = true;
//	}*/
//
//	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
//		if(GetMouseX() >= playerEntity->position.x - playerEntity->texture.width * 0.5f * GAME_SCALE &&
//			GetMouseX() <= playerEntity->position.x + playerEntity->texture.width * 0.5f * GAME_SCALE &&
//			GetMouseY() >= playerEntity->position.y - playerEntity->texture.height * 0.5f * GAME_SCALE &&
//			GetMouseY() <= playerEntity->position.y + playerEntity->texture.height * 0.5f * GAME_SCALE) {
//			playerEntityOnClick();
//		}
//	}
//}
//
//void playerEntityOnClick() {
//	//rotationAngle += 1.0f;
//	//playerEntity->active = false;
//	//printf("Player Clicked!\n");
//
//	Attacking = true;
//	createEntity(&allEntitys, &counts, &entityId, "Bullet1", "bullet.png",Vector2{ 0, 0 });
//	
//	Entity* _bulletEntity = findEntityById(entityId - 1);
//	_bulletEntity->actor.OnStart = playerBulletEntity_OnStart;
//	_bulletEntity->actor.OnUpdate = playerBulletEntity_OnUpdate;
//	_bulletEntity->actor.OnDraw = playerBulletEntity_OnDraw;
//	_bulletEntity->actor.OnDispose = playerBulletEntity_OnDispose;
//	_bulletEntity->actor.OnStart();
//}
//
//void playerEntity_OnDraw() {
//	DrawTexturePro(playerEntity->texture,
//		Rectangle {
//		0, 0, (float)playerEntity->texture.width, (float)playerEntity->texture.height
//	},
//		Rectangle {
//		playerEntity->position.x, playerEntity->position.y, playerEntity->texture.width* GAME_SCALE, playerEntity->texture.height* GAME_SCALE
//	},
//		Vector2 {
//		playerEntity->texture.width / 2 * GAME_SCALE, playerEntity->texture.height / 2 * GAME_SCALE
//	},
//		rotationAngle, WHITE);
//
//	RotateBoundingBox(playerEntity, rotationAngle);
//
//	if (playerEntity->drawBoundingBox) {
//		DrawBoundingBox(playerEntity->boundingBox, RED);
//	}
//}
//void playerEntity_OnDispose() {
//	UnloadTexture(playerEntity->texture);
//}
//
//// ==========================玩家子弹相关函数实现=========================
//
//void playerBulletEntity_OnStart() {
//	Entity* _bulletEntity = findEntityById(entityId - 1);
//	_bulletEntity->position.x = playerEntity->position.x;
//	_bulletEntity->position.y = playerEntity->position.y;
//}
//void playerBulletEntity_OnUpdate() {
//	if (Attacking) {
//		Entity* _bulletEntity = findEntityById(entityId - 1);
//		_bulletEntity->position.y -= bulletSpeed;
//		if (_bulletEntity->position.y <= 0) {
//			Attacking = false;
//			// 移除子弹实体
//			//removeEntity(&allEntitys, &counts, &(entityId - 1));
//		}
//	}
//	
//}
//void playerBulletEntityOnClick() {
//}
//void playerBulletEntity_OnDraw() {
//	Entity* _bulletEntity = findEntityById(entityId - 1);
//	DrawTexturePro(_bulletEntity->texture,
//		Rectangle {
//		0, 0,(float)_bulletEntity->texture.width, (float)_bulletEntity->texture.height
//	},
//		Rectangle {
//		_bulletEntity->position.x, _bulletEntity->position.y, _bulletEntity->texture.width* GAME_SCALE, _bulletEntity->texture.height* GAME_SCALE
//	},
//		Vector2 {
//		_bulletEntity->texture.width / 2 * GAME_SCALE, _bulletEntity->texture.height / 2 * GAME_SCALE
//	},
//		180, WHITE);
//}
//void playerBulletEntity_OnDispose() {
//	bulletSpeed = 2.0f;
//}
//
//// ==========================敌人相关函数实现=========================
//void enemyEntity_OnStart() {
//	//enemyEntity->drawBoundingBox = true;
//}
//void enemyEntity_OnUpdate() {
//	
//}
//void enemyEntityOnClick() {
//}
//void enemyEntity_OnDraw() {
//	DrawTexturePro(enemyEntity->texture,
//		Rectangle {
//		0, 0, (float)enemyEntity->texture.width, (float)enemyEntity->texture.height
//	},
//		Rectangle {
//		enemyEntity->position.x, enemyEntity->position.y, enemyEntity->texture.width* GAME_SCALE, enemyEntity->texture.height* GAME_SCALE
//	},
//		Vector2 {
//		enemyEntity->texture.width / 2 * GAME_SCALE, enemyEntity->texture.height / 2 * GAME_SCALE
//	},
//		rotationAngle, WHITE);
//	if (enemyEntity->drawBoundingBox) {
//		DrawBoundingBox(enemyEntity->boundingBox, RED);
//	}
//}
//void enemyEntity_OnDispose() {
//	UnloadTexture(enemyEntity->texture);
//}

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
void rotate_points_batch(Vector2 points[], int count,Vector2 center, double angle_deg) {
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
	rotate_points_batch(rectangle, n, Vector2 { _entity->position.x, _entity->position.y }, angle);

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
	_entity->boundingBox = BoundingBox{
	Vector3{
minX, minY, 0
},
Vector3 {
maxX, maxY, 0
}
	};
}