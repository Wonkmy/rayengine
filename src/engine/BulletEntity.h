#pragma once
#include "Entity.h"
#include "game.h"
#include "entityManager.h"

class BulletEntity :public Entity
{
	public:
	BulletEntity();
	~BulletEntity();
	void OnStart() override;
	void OnUpdate() override;
	void OnDraw() override;
	void OnDispose() override;
	void OnGUI() override;
	void OnCollisionEnter2D(Entity* other) override;
	bool isCollidingWithEnemy = false;
};

