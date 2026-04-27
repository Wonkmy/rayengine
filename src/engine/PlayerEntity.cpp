#include "PlayerEntity.h"
#include "raylib.h"

PlayerEntity::PlayerEntity() {
}

void PlayerEntity::OnStart() {
	this->drawBoundingBox = false;
	angle = 0.0f;
	active = true;
	position = Vector2{ 0.0f, 0.0f };
}

void PlayerEntity::OnUpdate() {
	position.x = GetMouseX() - GetScreenWidth() / 2;
	position.y = GetMouseY() - GetScreenHeight() / 2;
	UpdateBoundingBox();
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		if(IsClicked()){
			this->OnClicked();
		}
	}
}

void PlayerEntity::OnClicked() {
	BulletEntity* bulletEntity = new BulletEntity();
	bulletEntity->SetTag(TAG_BULLET);
	CreateEntity("Bullet1", BulletTexture, BulletEntityTexturePath, bulletEntity);
	bulletEntity->position = Vector2{ this->position.x,this->position.y - 75 };
}

void PlayerEntity::OnDraw() {
	DrawTexturePro(texture,
		Rectangle {
		0, 0, (float)texture.width, (float)texture.height
	},
	Rectangle {
		position.x, position.y, texture.width* GAME_SCALE, texture.height* GAME_SCALE
	},
	Vector2 {
		texture.width / 2 * GAME_SCALE, texture.height / 2 * GAME_SCALE
	},
	angle, WHITE);
	if (drawBoundingBox) {
		DrawBoundingBox(boundingBox, RED);
	}
}

void PlayerEntity::OnDispose() {
	active = false;
	UnloadTexture(texture);
}

void PlayerEntity::OnGUI() {
	
}

PlayerEntity::~PlayerEntity() {
}