#include "PlayerEntity.h"
void EntityManagerOnStart() {
	std::string playerName = "Player1";
	const char* playerTexturePath = "sprites/f1.png";
	auto playerEntity = PlayerEntity(playerName, playerTexturePath);
	playerEntity.OnStart();
	entitys.emplace_back(playerEntity);
}
void EntityManagerOnUpdate() {
    for (int i = 0; i < entitys.size(); ) {
        if (entitys[i].active) {
            entitys[i].OnUpdate();
        }
    }
}
//
void EntityManagerOnDraw() {
    for (int i = 0; i < entitys.size(); ) {
        if (entitys[i].active) {
            entitys[i].OnDraw();
        }
    }
}
void EntityManagerOnGUI() {
    for (int i = 0; i < entitys.size(); ) {
        if (entitys[i].active) {
            entitys[i].OnGUI();
        }
    }
//	//ImGuiImpl_CraeteDockSpace();// 创建DockSpace
//	//char finalText[100];
//	//snprintf(finalText, sizeof(finalText), "X: %.1f Y: %.1f\nName: %s", entity->position.x,entity->position.y, entity->name);
//	//ImGuiImpl_DrawHierarchy();
//	//ImGuiImpl_DrawText("Transform", 10, 50, "finalText");
//	/*for (int i = 0; i < count; i++)
//	{
//		if (!objects[i]->active) continue;
//		objects[i]->actor.OnGUI();
//	}*/
//	//ImGuiImpl_DrawSceneView();
}
void EntityManagerOnDispose() {
    for (int i = 0; i < entitys.size(); ) {
        if (entitys[i].active) {
            entitys[i].OnDispose();
        }
    }
}