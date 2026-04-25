#pragma once
#ifndef PlayerEntity_H
#define PlayerEntity_H
#include "Entity.h"
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
};

#endif // PlayerEntity_H