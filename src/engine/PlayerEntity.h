#pragma once
#ifndef PlayerEntity_H
#define PlayerEntity_H
#include "Entity.h"
#include "BulletEntity.h"
#include "EnemyEntity.h"
#include <string>
#include "game.h"
using namespace std;

class PlayerEntity : public Entity
{
public:
    PlayerEntity();
    ~PlayerEntity();
    void OnStart() override;
    void OnUpdate() override;
    void OnDraw() override;
    void OnDispose() override;
    void OnGUI() override;

    void OnClicked();
};

#endif // PlayerEntity_H