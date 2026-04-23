#include "game.h"
void playerEntity_OnStart() {
	
}
void playerEntity_OnUpdate() {
	playerEntity->position.x = GetMouseX();
	playerEntity->position.y = GetMouseY();
	UpdateBoundingBox(playerEntity);
}
void playerEntity_OnDraw() {

	DrawTexturePro(playerEntity->texture,
		(Rectangle) {
		0, 0, playerEntity->texture.width, playerEntity->texture.height
	},
		(Rectangle) {
		playerEntity->position.x, playerEntity->position.y, playerEntity->texture.width* GAME_SCALE, playerEntity->texture.height* GAME_SCALE
	},
		(Vector2) {
		playerEntity->texture.width / 2 * GAME_SCALE, playerEntity->texture.height / 2 * GAME_SCALE
	},
		0.0f, WHITE);

	if (playerEntity->drawBoundingBox) {
		DrawBoundingBox(playerEntity->boundingBox, RED);
	}
}
void playerEntity_OnDispose() {

}