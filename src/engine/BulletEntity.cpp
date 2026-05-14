#include "BulletEntity.h"
#include "EnemyEntity.h"

BulletEntity::BulletEntity() {
}

void BulletEntity::OnStart() {
	angle = 180.0f;
	active = true;
	this->drawBoundingBox = true;
	position = Vector2{ 0.0f, 0.0f };
	this->collider = Collider{ boundingBox, false, false };
	this->isCollidingWithEnemy = false;
}

void BulletEntity::OnUpdate() {
	if (!this->active)return;
	// 这里可以添加子弹的移动逻辑
	this->position.y -= 5.0f; // 例如，子弹向上移动
	// 更新子弹的边界框
	UpdateBoundingBox();
	/*EnemyEntity* enemyEntity = GetEntityByTag<EnemyEntity>(TAG_ENEMY);*/
	// 由于可能存在多个敌人实体，这里我们需要遍历所有敌人实体来检测碰撞
	for (int i = entitys.size() - 1; i > 0 ; i--) {
		if (entitys[i]->active && entitys[i]->tag == TAG_ENEMY) {
			EnemyEntity* enemyEntity = dynamic_cast<EnemyEntity*>(entitys[i].get());
			if (enemyEntity != nullptr) {
				bool isCollision = CheckEntityCollision(this->name.c_str(), enemyEntity->name.c_str());
				if (isCollision) {
					OnCollisionEnter2D(enemyEntity);
					break;
				}
				else {
					// 如果当前帧没有碰撞，重置标志以允许下一次碰撞检测
					this->isCollidingWithEnemy = false;
				}
			}
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

void BulletEntity::OnCollisionEnter2D(Entity* other) {
	if (other->tag == TAG_ENEMY) {
		if (this->isCollidingWithEnemy == false) {
			// 只有当之前没有与敌人发生碰撞时才处理碰撞逻辑
			this->isCollidingWithEnemy = true; // 设置标志，表示已经与敌人发生碰撞
			EnemyEntity* enemyEntity = dynamic_cast<EnemyEntity*>(other);
			if (enemyEntity != nullptr) {
				enemyEntity->TakeDamage(20);
				RemoveEntity(this->id);
			}
		}
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