#pragma once
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"

typedef struct TextureRegister {
	int id;
	Texture2D texture;
} TextureRegister;

// 生命周期函数
void EntityManagerOnStart();
void EntityManagerOnUpdate();
void EntityManagerOnDraw();
void EntityManagerOnGUI();
void EntityManagerOnDispose();

// 实体管理函数
void CreateEntity(const char* _name, const char* _texturePath,Entity* _entity);
void CreateEntity(const char* _name, int resid, const char* _texturePath, Entity* _entity);
void RemoveEntity(int id);
Entity* GetEntityById(int id);
bool CheckEntityCollision(int id1, int id2);

// 纹理管理函数
TextureRegister* GetTextureById(int id);
Texture2D LoadTextureToPool(int id, const char* texturePath);

// 工具函数
void RotateBoundingBox(Entity* _entity, float angle);

extern std::vector<std::unique_ptr<TextureRegister>> allTexturePool;


#endif // DEBUG