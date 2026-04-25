#include "PlayerEntity.h"
#include "raylib.h"
void UpdateBoundingBox(Entity* entity) {
	Vector3 min = Vector3{ entity->position.x - entity->texture.width / 2 * GAME_SCALE, entity->position.y - entity->texture.height / 2 * GAME_SCALE };
	Vector3 max = Vector3{ entity->position.x + entity->texture.width / 2 * GAME_SCALE,  entity->position.y + entity->texture.height / 2 * GAME_SCALE };
	entity->boundingBox = BoundingBox{ min, max };
}
//
//void updateNewPosition(Vector2* currentPosition, Vector2* targetPosition) {
//	currentPosition->x = targetPosition->x;
//	currentPosition->y = targetPosition->y;
//}
PlayerEntity::PlayerEntity() {
}

void PlayerEntity::OnStart() {
	//playerEntity->drawBoundingBox = true;
	active = true;
	position = Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
}

void PlayerEntity::OnUpdate() {
	position.x = GetMouseX();
	position.y = GetMouseY();
	
	UpdateBoundingBox(this);
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		if(GetMouseX() >= position.x - texture.width * 0.5f * GAME_SCALE &&
			GetMouseX() <= position.x + texture.width * 0.5f * GAME_SCALE &&
			GetMouseY() >= position.y - texture.height * 0.5f * GAME_SCALE &&
			GetMouseY() <= position.y + texture.height * 0.5f * GAME_SCALE) {
			// 这里可以调用一个函数来处理点击
		}
	}
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