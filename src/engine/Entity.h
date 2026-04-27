#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include "raylib.h" 
#include <vector>
#include <memory>

#define PlayerEntityTexturePath1 "assets/sprites/f1.png"
#define PlayerEntityTexturePath2 "assets/sprites/f2.png"
#define BulletEntityTexturePath "assets/sprites/bullet.png"


using namespace std;
class Entity {
public:
	explicit Entity();
	virtual ~Entity();
	string name;
	int id;
	bool active;
	bool _isClicked;
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
	virtual void UpdateBoundingBox();
	virtual bool IsClicked();
};
// Entity相关
extern std::vector<std::unique_ptr<Entity>> entitys;
extern int globalEntityId;// 全局实体ID计数器
extern int globalResetId;// 全局资源ID计数器
extern enum ResourceId {
	PlayerTexture = 1,
	BulletTexture = 2,
	EnemyTexture = 3,
};

#endif // ENTITY_H