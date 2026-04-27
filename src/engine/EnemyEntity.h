#pragma once
//#include "Entity.h"
#include "game.h"
#include "imgui.h"
#include "entityManager.h"

class EnemyEntity : public Entity
{
    public:
    EnemyEntity();
	~EnemyEntity();
    void OnStart() override;
    void OnUpdate() override;
    void OnDraw() override;
    void OnGUI() override;
	void OnDispose() override;

    void DrawBloodBar();
    void TakeDamage(int damage);
};