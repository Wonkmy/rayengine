#include "PlayerEntity.h"
std::vector<std::unique_ptr<Entity>> entitys;
std::vector<std::unique_ptr<TextureRegister>> allTexturePool;

int globalEntityId = 0;// 全局实体ID计数器
int globalResetId = 0;// 全局资源ID计数器
void EntityManagerOnStart() {
	PlayerEntity* playerEntity = new PlayerEntity();
	playerEntity->SetTag(TAG_PLAYER);
	CreateEntity("Player1", PlayerTexture, PlayerEntityTexturePath1, playerEntity);

	EnemyEntity* enemyEntity = new EnemyEntity();
	enemyEntity->SetTag(TAG_ENEMY);
	CreateEntity("Enemy1", PlayerTexture_2, PlayerEntityTexturePath2, enemyEntity);
	enemyEntity->position = Vector2{ 200.0f, -150.0f };
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
	//ImGuiImpl_DrawText("Transform", 10, 50, "finalText");
//	/*for (int i = 0; i < count; i++)
//	{
//		if (!objects[i]->active) continue;
//		objects[i]->actor.OnGUI();
//	}*/
//	//ImGuiImpl_DrawSceneView();
}
void EntityManagerOnDispose() {
	// 销毁所有实体
    for (int i = 0; i < entitys.size(); ) {
        if (entitys[i]->active) {
            entitys[i]->OnDispose();
			// 从entitys中移除已销毁的实体
			entitys.erase(entitys.begin() + i);
		}
    }
	entitys.clear();
	// 清空全局纹理池
	for (int i = 0; i < allTexturePool.size(); i++) {
		UnloadTexture(allTexturePool[i]->texture);
	}
	allTexturePool.clear();
}
void CreateEntity(const char* _name, int resid, const char* _texturePath, Entity* _entity) {
	std::string playerName = _name;
	const char* playerTexturePath = _texturePath;
	Texture2D tex = LoadTextureToPool(resid, _texturePath);
	_entity->id = globalEntityId++;
	_entity->name = playerName;
	_entity->texture = tex;
	_entity->OnStart();
	entitys.emplace_back(_entity);
}
void CreateEntity(const char* _name, const char* _texturePath, Entity* _entity) {
	std::string playerName = _name;
	const char* playerTexturePath = _texturePath;
	
	Texture2D tex = LoadTexture(_texturePath);
	_entity->id = globalEntityId++;
	_entity->name = playerName;
	_entity->texture = tex;
	_entity->OnStart();
	entitys.emplace_back(_entity);
}
void RemoveEntity(int id) {
	// 第一种方式
	//for (int i = 0; i < entitys.size(); i++) {
	//	if (entitys[i]->id == id) {
	//		entitys[i]->id = -1; // 标记为已销毁
	//		entitys[i]->OnDispose();
	//		entitys.erase(entitys.begin() + i);
	//		break;
	//	}
	//}

	// 第二种方式
	entitys.erase(
		std::remove_if(entitys.begin(), entitys.end(),
			[id](const std::unique_ptr<Entity>& e) {
				if (e->id == id) {
					e->OnDispose();
					return true;
				}
				return false;
			}),
		entitys.end()
	);

	// 第三种方式
	//for (auto it = entitys.begin(); it != entitys.end(); ++it) {
	//	if ((*it)->id == id) {
	//		(*it)->OnDispose(); // 清理
	//		entitys.erase(it);  // 删除
	//		break;
	//	}
	//}

}
Entity* GetEntityById(int id) {
	if(entitys.size() > 0){
		for (int i = 0; i < entitys.size(); i++)
		{
			if (entitys[i]->id == id) {
				return entitys[i].get();
			}
		}
	}
}

Entity* GetEntityByName(const char* name) {
	if (entitys.size() > 0) {
		for (int i = 0; i < entitys.size(); i++)
		{
			if (entitys[i]->name == name) {
				return entitys[i].get();
			}
		}
		return nullptr; // 如果没有找到，返回nullptr
	}
}

Entity* GetEntityByTag(const char* tag) {
	if (entitys.size() > 0) {
		for (int i = 0; i < entitys.size(); i++)
		{
			if (entitys[i]->tag == tag) {
				return entitys[i].get();
			}
		}
		return nullptr; // 如果没有找到，返回nullptr
	}
}


bool CheckEntityCollision(const char* name1, const char* name2) {
	auto entity1 = GetEntityByName(name1);
	auto entity2 = GetEntityByName(name2);
	if (entity1 == nullptr || entity2 == nullptr) {
		return false; // 如果任一实体不存在，返回false
	}
	return CheckCollisionBoxes(entity1->boundingBox, entity2->boundingBox);
}

TextureRegister* GetTextureById(int id) {
	if (allTexturePool.size() > 0) {
		for (int i = 0; i < allTexturePool.size(); i++)
		{
			if (allTexturePool[i]->id == id) {
				return allTexturePool[i].get();
			}
		}
	}
}
Texture2D LoadTextureToPool(int id, const char* texturePath) {
	if (allTexturePool.size() > 0) {
		for (int i = 0; i < allTexturePool.size(); i++) {
			if (allTexturePool[i]->id == id) {
				return allTexturePool[i]->texture;
			}
		}
	}

	// 如果allTexturePool中不存在相同id的纹理，则加载并添加
	Texture2D tex = LoadTexture(texturePath);
	// 将纹理添加到全局纹理池中
	TextureRegister* newTextureRegister = new TextureRegister{ id, tex };
	allTexturePool.emplace_back(newTextureRegister);
	return tex;
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