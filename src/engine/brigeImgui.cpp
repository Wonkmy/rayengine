
#include "imgui.h"
#include "brigeImgui.h"
#include <imgui_internal.h>

Node nodes[] = {
    {"Root", 0, -1},
    {"Player", 1, 0},
    {"Camera", 2, 1},
    {"Enemy", 3, 0},
};
int nodeCount = 4;

int selectedId = -1; // 当前选中

void ImGuiImpl_Init()
{
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // 开启Dock
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // 可选：多窗口（拖出主窗口）
}

void ImGuiImpl_DrawText(const char* name,float p_x, float p_y, const char* fmt,...)
{
    //ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove;
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Always);
    ImGui::Begin(name);
    ImGui::SetCursorPos(ImVec2(p_x, p_y));
    ImGui::Text(fmt);
    if (selectedId != -1) {
        ImGui::Text(nodes[selectedId].name);
    }
    ImGui::End();
}

void ImGuiImpl_CraeteDockSpace()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

    // 全屏窗口
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    window_flags |= ImGuiWindowFlags_NoBackground;
    ImGui::Begin("DockSpace Window", NULL, window_flags);

    // 创建Dock区域
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

    ImGui::End();
}



void ImGuiImpl_DrawHierarchy()
{
    ImGui::Begin("Hierarchy");

    for (int i = 0; i < nodeCount; i++)
    {
        // 只画根节点
        if (nodes[i].parent != -1) continue;

        DrawNode(i);
    }

    ImGui::End();
}

void DrawNode(int index)
{
    Node* node = &nodes[index];

    // 是否被选中
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

    if (selectedId == node->id)
        flags |= ImGuiTreeNodeFlags_Selected;

    // 是否有子节点
    bool hasChild = false;
    for (int i = 0; i < nodeCount; i++)
    {
        if (nodes[i].parent == node->id)
        {
            hasChild = true;
            break;
        }
    }

    if (!hasChild)
        flags |= ImGuiTreeNodeFlags_Leaf;

    bool opened = ImGui::TreeNodeEx(
        (void*)(intptr_t)node->id,
        flags,
        "%s",
        node->name
    );

    // 点击选中
	if (ImGui::IsItemClicked())// 此函数不填参数表示左键点击 
    {
        selectedId = node->id;
    }

    if (opened)
    {
        // 递归画子节点
        for (int i = 0; i < nodeCount; i++)
        {
            if (nodes[i].parent == node->id)
            {
                DrawNode(i);
            }
        }

        ImGui::TreePop();
    }
}

// 这个函数用来绘制引擎中常用的Scene窗口，包含场景视图、属性编辑器等
void ImGuiImpl_DrawSceneView()
{
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_Always);
    ImGui::Begin("Scene");
    ImGui::Text("Scene View");
    ImGui::End();
}

void ImGuiImpl_DrawGameView() {

}