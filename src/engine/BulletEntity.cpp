#include "BulletEntity.h"

BulletEntity::BulletEntity() {
}

void BulletEntity::OnStart() {
	angle = 0.0f;
	active = true;
	drawBoundingBox = true;
	position = Vector2{ 0.0f, 0.0f };
}

void BulletEntity::OnUpdate() {
	if (!this->active)return;
	// 这里可以添加子弹的移动逻辑
	this->position.y -= 5.0f; // 例如，子弹向上移动
	// 更新子弹的边界框
	if (drawBoundingBox) {
		UpdateBoundingBox();
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