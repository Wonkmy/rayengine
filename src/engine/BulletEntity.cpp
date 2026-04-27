#include "BulletEntity.h"
#include "EnemyEntity.h"

BulletEntity::BulletEntity() {
}

void BulletEntity::OnStart() {
	angle = 180.0f;
	active = true;
	this->drawBoundingBox = false;
	position = Vector2{ 0.0f, 0.0f };
}

void BulletEntity::OnUpdate() {
	if (!this->active)return;
	// 这里可以添加子弹的移动逻辑
	this->position.y -= 5.0f; // 例如，子弹向上移动
	// 更新子弹的边界框
	UpdateBoundingBox();

	EnemyEntity* enemyEntity = GetEntityByTag<EnemyEntity>(TAG_ENEMY);
	if (enemyEntity != NULL) {
		bool isColliding = CheckEntityCollision(this->name.c_str(), enemyEntity->name.c_str()); // 检测与敌人实体的碰撞
		if (isColliding) {
			enemyEntity->TakeDamage(20); // 对敌人造成伤害
			RemoveEntity(this->id);
		}
	}

	if (this->position.y <= -GetScreenHeight() * 0.5f) {
		RemoveEntity(this->id); // 当子弹移出屏幕时，销毁它
	}
}

void BulletEntity::OnDraw() {
	if (!this->active)return;
	DrawTexturePro(this->texture,
		Rectangle {
		0, 0, (float)this->texture.width, (float)this->texture.height
	},
	Rectangle {
		this->position.x, this->position.y, this->texture.width* GAME_SCALE, this->texture.height* GAME_SCALE
	},
	Vector2 {
		this->texture.width / 2 * GAME_SCALE, this->texture.height / 2 * GAME_SCALE
	},
	angle, WHITE);
	if (drawBoundingBox) {
		DrawBoundingBox(boundingBox, RED);
	}
}

void BulletEntity::OnDispose() {
	active = false;
	drawBoundingBox = false;
}

void BulletEntity::OnGUI() {

}

BulletEntity::~BulletEntity() {
}