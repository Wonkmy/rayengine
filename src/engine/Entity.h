#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include "raylib.h" 
#include <vector>


using namespace std;
class Entity {
public:
	explicit Entity(string _name, const char* path);
	virtual ~Entity();
	string name;
	int id;
	bool active;
	float angle;
	Vector2 position;
	Texture2D texture;
	BoundingBox boundingBox;
	bool drawBoundingBox;
	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnDraw();
	virtual void OnGUI();
	virtual void OnDispose();
};
// Entity相关
std::vector<Entity> entitys; // 全局实体列表
#endif // ENTITY_H