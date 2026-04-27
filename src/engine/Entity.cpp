#include "entity.h"
#include "game.h"
Entity::Entity() {
}

void Entity::OnStart() {
}

void Entity::OnUpdate() {
}

void Entity::OnDraw() {}

void Entity::OnGUI() {}

void Entity::OnDispose() {
}

void Entity::UpdateBoundingBox() {
	Vector3 min = Vector3{ this->position.x - this->texture.width / 2 * GAME_SCALE, this->position.y - this->texture.height / 2 * GAME_SCALE };
	Vector3 max = Vector3{ this->position.x + this->texture.width / 2 * GAME_SCALE,  this->position.y + this->texture.height / 2 * GAME_SCALE };
	this->boundingBox = BoundingBox{ min, max };
}

bool Entity::IsClicked(){
	if (GetMouseX() - GetScreenWidth() * 0.5f >= this->position.x - this->texture.width * 0.5f * GAME_SCALE &&
		GetMouseX() - GetScreenWidth() * 0.5f <= this->position.x + this->texture.width * 0.5f * GAME_SCALE &&
		GetMouseY() - GetScreenHeight() * 0.5f >= this->position.y - this->texture.height * 0.5f * GAME_SCALE &&
		GetMouseY() - GetScreenHeight() * 0.5f <= this->position.y + this->texture.height * 0.5f * GAME_SCALE) {
		return true;
	}
	else {
		return false;
	}
}

void Entity::SetTag(const char* _tag) {
	if(_tag != nullptr){
		this->tag = _tag;
	}
	else {
		this->tag = "Default";
	}
}

Entity::~Entity() {
}