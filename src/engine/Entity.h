#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include "raylib.h" 
#include <vector>
#include <memory>
#include "TagManager.h"
#include "brigeImgui.h"

#define PlayerEntityTexturePath1 "assets/sprites/p1.png"
#define PlayerEntityTexturePath2 "assets/sprites/f2.png"
#define EnemyEntityTexturePath "assets/sprites/p2.png"
#define BulletEntityTexturePath "assets/sprites/bullet.png"

typedef struct Collider {
	BoundingBox box;
	bool isColliding;     // 当前帧
	bool wasColliding;    // 上一帧
} Collider;

using namespace std;
class Entity {
public:
	explicit Entity();
	virtual ~Entity();
	string name;
	string tag;
	int id;
	bool active;
	bool _isClicked;
	float angle;
	Vector2 position;
	Texture2D texture;
	BoundingBox boundingBox;
	Collider collider;
	bool drawBoundingBox;
	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnDraw();
	virtual void OnGUI();
	virtual void OnDispose();
	virtual void UpdateBoundingBox();
	virtual bool IsClicked();
	virtual void SetTag(const char* _tag);
	virtual void OnCollisionEnter2D(Entity* other);
};
// Entity相关
extern std::vector<std::unique_ptr<Entity>> entitys;
extern int globalEntityId;// 全局实体ID计数器
extern int globalResetId;// 全局资源ID计数器
extern enum ResourceId {
	PlayerTexture = 1,
	PlayerTexture_2 = 2,
	BulletTexture = 3,
	EnemyTexture = 4,
};

#endif // ENTITY_H