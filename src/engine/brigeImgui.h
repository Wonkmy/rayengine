#pragma once
#ifndef BRIGE_IMPL_API
#define BRIGE_IMPL_API

typedef struct Node {
    const char* name;
    int id;
    int parent; // 父节点索引，-1表示根
} Node;
void DrawNode(int index);
void ImGuiImpl_Init();
void ImGuiImpl_DrawText(const char* name, int p_x, int p_y, const char* fmt, ...);
void ImGuiImpl_CraeteDockSpace();
void ImGuiImpl_DrawHierarchy();
void DrawNode(int index);
void ImGuiImpl_DrawSceneView();
void ImGuiImpl_DrawGameView();

#endif // IMGUI_IMPL_API