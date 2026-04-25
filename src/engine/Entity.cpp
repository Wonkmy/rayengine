#include "entity.h"
#include "game.h"

Entity::Entity(string _name,const char* texPath) {
	// 修复：不能直接用字符串拼接，需要用 std::string 处理
	std::string texPathStr = GAME_ASSETS_ROOT_PATH + std::string(texPath);
	texture = LoadTexture(texPathStr.c_str());
}

void Entity::OnStart() {}

void Entity::OnUpdate() {}

void Entity::OnDraw() {}

void Entity::OnGUI() {}

void Entity::OnDispose() {}

Entity::~Entity() {
}