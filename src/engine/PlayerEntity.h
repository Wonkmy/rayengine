#pragma once
#ifndef PlayerEntity_H
#define PlayerEntity_H
#include "Entity.h"
#include <string>
using namespace std;

class PlayerEntity : public Entity
{
public:
    explicit PlayerEntity(string _name, const char* _texPath);
    ~PlayerEntity();
    void OnStart() override;
    void OnUpdate() override;
    void OnDraw() override;
    void OnDispose() override;
    void OnGUI() override;
};

#endif // PlayerEntity_H