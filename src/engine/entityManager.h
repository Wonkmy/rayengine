#pragma once
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
void EntityManagerOnStart();
void EntityManagerOnUpdate();
void EntityManagerOnDraw();
void EntityManagerOnGUI();
void EntityManagerOnDispose();

void RotateBoundingBox(Entity* _entity, float angle);
#endif // DEBUG