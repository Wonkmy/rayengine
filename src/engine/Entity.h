#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include "raylib.h" 
#include <vector>
#include <memory>


using namespace std;
class Entity {
public:
	explicit Entity();
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
extern std::vector<std::unique_ptr<Entity>> entitys;
#endif // ENTITY_H