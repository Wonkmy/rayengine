/*
==========================================================
                MiniUI.h 使用说明 / README
                Author: Wonkmy
				Data: 2026-05-05
				Time: 11:00
==========================================================

一个基于 raylib 的极简 Immediate Mode UI 系统

特点：
- 无组件树（Immediate Mode）
- 无复杂依赖
- 单头文件
- 支持布局、输入、滚动、锚点
- 适用于游戏内 UI（非复杂编辑器）

==========================================================
一、基础使用
==========================================================

1. 在一个 .c / .cpp 文件中定义实现：

    #define MINIUI_IMPLEMENTATION
    #include "miniui.h"

2. 其他文件只 include：

    #include "miniui.h"

==========================================================
二、推荐使用方式（重要）
==========================================================

使用“设计分辨率 + Camera2D 缩放 UI”
miniui 内部不处理缩放

示例：

    Camera2D uiCam = {0};

    float scaleX = GetScreenWidth()  / 1920.0f;
    float scaleY = GetScreenHeight() / 1080.0f;
    float scale  = scaleX < scaleY ? scaleX : scaleY;

    uiCam.zoom = scale;
    uiCam.offset = (Vector2){0, 0};
    uiCam.target = (Vector2){0, 0};

    BeginMode2D(uiCam);

    UI_Begin();

    // UI绘制

    EndMode2D();

==========================================================
三、输入（非常重要）
==========================================================

如果使用 Camera2D：

    Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), camera);

miniui 内部所有鼠标判断应使用该坐标

否则点击会偏移 ❗

==========================================================
四、布局系统
==========================================================

核心函数：

    BeginVertical(x, y, width)
    BeginHorizontal(x, y, width)
    EndLayout()

内部通过 UI_GetNextRect 自动排布

----------------------------------------------------------

示例：

    BeginVertical(20, 20, 200);

    Button("Start");
    Button("Exit");

    EndLayout();

----------------------------------------------------------

获取元素位置：

    Rectangle r = UI_GetNextRect(w, h);

说明：

    w > 0  → 使用指定宽度
    w <= 0 → 在 Vertical 中自动填满容器宽度

==========================================================
五、基础控件
==========================================================

1. Button

    if (Button("Start"))
    {
        // 点击
    }

----------------------------------------------------------

2. Slider

    float value = 0.5f;

    Slider("Volume", &value, 0.0f, 1.0f);

----------------------------------------------------------

3. InputText

    char name[32] = "Player";

    InputText("Name", name, 32);

==========================================================
六、自定义绘制（推荐方式）
==========================================================

使用布局获取位置，再自行绘制：

    Rectangle r = UI_GetNextRect(100, 50);
    DrawRectangleRec(r, GRAY);

注意：

    布局尺寸 >= 实际绘制尺寸

否则会：
- 重叠
- ScrollView 错乱
- 点击异常

==========================================================
七、ScrollView（滚动视图）
==========================================================

支持：
横向 / 纵向
鼠标滚轮
鼠标拖动

----------------------------------------------------------

使用方式：

    float scroll = 0;

    BeginScrollView(200, 150, &scroll, UI_SCROLL_VERTICAL);

    for (int i = 0; i < 20; i++)
    {
        Button("Item");
    }

    EndScrollView();

----------------------------------------------------------

横向：

    BeginScrollView(200, 100, &scroll, UI_SCROLL_HORIZONTAL);

----------------------------------------------------------

注意：

ScrollView 内必须使用 UI_GetNextRect
不要使用固定坐标绘制

==========================================================
八、Anchor（锚点定位）
==========================================================

    Rectangle AnchorRect(parent, w, h, anchor);

anchor：

    0 = 左上
    1 = 右上
    2 = 左下
    3 = 右下

----------------------------------------------------------

示例：

    Rectangle screen = {
        0, 0,
        GetScreenWidth(),
        GetScreenHeight()
    };

    Rectangle btn = AnchorRect(screen, 120, 40, 1);

    DrawRectangleRec(btn, GRAY);

----------------------------------------------------------

常用组合：

    // 面板 + 布局
    Rectangle panel = AnchorRect(screen, 200, 300, 1);

    BeginVertical(panel.x + 10, panel.y + 10, panel.width - 20);
    Button("A");
    EndLayout();

==========================================================
九、系统设计原则（重要）
==========================================================

miniui 遵循：

1. 布局负责位置（UI_GetNextRect）
2. 控件负责行为（Button / Slider）
3. 绘制负责表现（DrawXXX）
4. Camera 负责适配（缩放）

----------------------------------------------------------

不要做：

在 miniui 内部做缩放
手动 x * scale / y * scale
绕过 UI_GetNextRect 布局

==========================================================
十、总结
==========================================================

这是一套：

极简
可控
可扩展
面向游戏内 UI

的 UI 系统

适用于：

- 游戏 HUD
- 面板 UI
- 简易编辑工具

不适用于：

- 复杂富文本 UI
- 企业级界面系统

==========================================================
*/

#ifndef MINIUI_H
#define MINIUI_H

#define UI_SCROLL_VERTICAL   0
#define UI_SCROLL_HORIZONTAL 1

#include "raylib.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

    //=========================
    // 基础结构
    //=========================

    typedef struct {
        Rectangle rect;
        float cursorX;
        float cursorY;
        float spacing;
        int isVertical;
    } Layout;

#define UI_MAX_LAYOUT 16

    typedef struct {
        Rectangle viewRect;
        float* externalScroll;
        float scroll;
        float contentStart;
        float contentSize;

        int axis;

        int dragging;
        float lastMouse;
    } ScrollView;

#define UI_MAX_SCROLL 8

    static ScrollView scrollStack[UI_MAX_SCROLL];
    static int scrollTop = -1;

    //=========================
    // API 声明
    //=========================

    void UI_Begin();

    void BeginVertical(float x, float y, float width);
    void BeginHorizontal(float x, float y, float width);
    void EndLayout();

    bool Button(const char* text);
    float Slider(const char* label, float* value, float min, float max);
    void InputText(const char* label, char* buffer, int maxLen);

    Rectangle AnchorRect(Rectangle parent, float w, float h, int anchor);

    //=========================
#ifdef MINIUI_IMPLEMENTATION
//=========================

// 全局状态（极简）
    static Layout layoutStack[UI_MAX_LAYOUT];
    static int layoutTop = -1;

    static int ui_idCounter = 0;
    static int ui_activeInput = -1;
    static int ui_hotId = -1;

    //=========================
    // Frame Begin
    //=========================
    void UI_Begin()
    {
        ui_idCounter = 0;
        ui_hotId = -1;
    }

    //=========================
    // Layout
    //=========================

    void BeginVertical(float x, float y, float width)
    {
        layoutTop++;

        layoutStack[layoutTop].rect = Rectangle{ x, y, width, 0 };
        layoutStack[layoutTop].cursorX = x;
        layoutStack[layoutTop].cursorY = y;
        layoutStack[layoutTop].spacing = 5;
        layoutStack[layoutTop].isVertical = 1;
    }

    void BeginHorizontal(float x, float y, float width)
    {
        layoutTop++;

        layoutStack[layoutTop].rect.x = x;
        layoutStack[layoutTop].rect.y = y;
        layoutStack[layoutTop].rect.width = width;
        layoutStack[layoutTop].rect.height = 0;

        layoutStack[layoutTop].cursorX = x;
        layoutStack[layoutTop].cursorY = y;

        layoutStack[layoutTop].spacing = 5;
        layoutStack[layoutTop].isVertical = 0;
    }

    void EndLayout()
    {
        layoutTop--;
    }

    // 获取布局位置（核心）
    static Rectangle UI_GetNextRect(float w, float h)
    {
        Layout* l = &layoutStack[layoutTop];

        // ===== 新增：自动宽度支持（仅 Vertical）=====
        float finalW = w;

        // 如果是竖向布局，并且传入宽度 <= 0，则自动填满容器宽度
        if (l->isVertical && w <= 0)
        {
            finalW = l->rect.width;
        }

        Rectangle r = { l->cursorX, l->cursorY, finalW, h };

        // ===== 原有布局推进逻辑（保持不变）=====
        if (l->isVertical)
            l->cursorY += h + l->spacing;
        else
            l->cursorX += finalW + l->spacing; // 这里同步用 finalW

        return r;
    }

    //=========================
    // Button
    //=========================
    bool Button(const char* text)
    {
        int id = ui_idCounter++;
        Rectangle r = UI_GetNextRect(120, 30);

        Vector2 m = GetMousePosition();
        bool hover = CheckCollisionPointRec(m, r);

        if (hover) ui_hotId = id;

        bool click = (ui_hotId == id) &&
            hover &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        DrawRectangleRec(r, hover ? LIGHTGRAY : GRAY);
        DrawText(text, (int)r.x + 10, (int)r.y + 8, 20, BLACK);

        return click;
    }

    //=========================
    // Slider
    //=========================
    float Slider(const char* label, float* value, float min, float max)
    {
        int id = ui_idCounter++;

        // ===== Label 单独一行 =====
        Rectangle labelRect = UI_GetNextRect(200, 20);
        DrawText(label, (int)labelRect.x, (int)labelRect.y, 18, BLACK);

        // ===== Slider 本体 =====
        Rectangle r = UI_GetNextRect(200, 30);

        Vector2 m = GetMousePosition();
        bool hover = CheckCollisionPointRec(m, r);

        if (hover) ui_hotId = id;

        if ((ui_hotId == id) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            float t = (m.x - r.x) / r.width;
            if (t < 0) t = 0;
            if (t > 1) t = 1;

            *value = min + t * (max - min);
        }

        // 背景
        DrawRectangleRec(r, DARKGRAY);

        // 滑块
        float t = (*value - min) / (max - min);
        float knobX = r.x + t * r.width;

        DrawCircle((int)knobX, (int)(r.y + r.height / 2), 6, WHITE);

        return *value;
    }

    //=========================
    // InputText
    //=========================
    void InputText(const char* label, char* buffer, int maxLen)
    {
        int id = ui_idCounter++;

        // ===== Label 单独一行 =====
        Rectangle labelRect = UI_GetNextRect(200, 20);
        DrawText(label, (int)labelRect.x, (int)labelRect.y, 18, BLACK);

        // ===== 输入框本体 =====
        Rectangle r = UI_GetNextRect(200, 30);

        Vector2 m = GetMousePosition();
        bool hover = CheckCollisionPointRec(m, r);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (hover)
                ui_activeInput = id;
            else if (ui_activeInput == id)
                ui_activeInput = -1;
        }

        // ===== 输入逻辑 =====
        if (ui_activeInput == id)
        {
            int key = GetCharPressed();

            while (key > 0)
            {
                int len = (int)strlen(buffer);

                if (len < maxLen - 1)
                {
                    buffer[len] = (char)key;
                    buffer[len + 1] = '\0';
                }

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                int len = (int)strlen(buffer);
                if (len > 0)
                    buffer[len - 1] = '\0';
            }
        }

        // ===== 绘制 =====
        DrawRectangleRec(r, ui_activeInput == id ? WHITE : LIGHTGRAY);
        DrawText(buffer, (int)r.x + 5, (int)r.y + 8, 20, BLACK);
    }

    //=========================
    // Anchor（极简）
    //=========================
    Rectangle AnchorRect(Rectangle parent, float w, float h, int anchor)
    {
        Rectangle r = { 0 };

        switch (anchor)
        {
        case 0: // 左上
            r.x = parent.x;
            r.y = parent.y;
            break;
        case 1: // 右上
            r.x = parent.x + parent.width - w;
            r.y = parent.y;
            break;
        case 2: // 左下
            r.x = parent.x;
            r.y = parent.y + parent.height - h;
            break;
        case 3: // 右下
            r.x = parent.x + parent.width - w;
            r.y = parent.y + parent.height - h;
            break;
        }

        r.width = w;
        r.height = h;

        return r;
    }

    bool BeginScrollView(float width, float height, float* scroll, int axis)
    {
        Rectangle r = UI_GetNextRect(width, height);

        scrollTop++;

        ScrollView* sv = &scrollStack[scrollTop];

        sv->viewRect = r;
        sv->externalScroll = scroll;
        sv->scroll = *scroll;
        sv->contentSize = 0;
        sv->axis = axis;

        Vector2 m = GetMousePosition();

        // ===== 滚轮 =====
        if (CheckCollisionPointRec(m, r))
        {
            float wheel = GetMouseWheelMove();
            sv->scroll -= wheel * 20;
        }

        // ===== 鼠标拖动 =====

        float mouseAxis = (axis == UI_SCROLL_VERTICAL) ? m.y : m.x;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(m, r))
        {
            sv->dragging = 1;
            sv->lastMouse = mouseAxis;
        }

        if (sv->dragging && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            float delta = mouseAxis - sv->lastMouse;
            sv->scroll -= delta;
            sv->lastMouse = mouseAxis;
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            sv->dragging = 0;
        }

        if (sv->scroll < 0)
            sv->scroll = 0;

        BeginScissorMode((int)r.x, (int)r.y, (int)r.width, (int)r.height);

        // ===== 关键：布局偏移 =====

        if (axis == UI_SCROLL_VERTICAL)
        {
            BeginVertical(r.x, r.y - sv->scroll, r.width);
            sv->contentStart = r.y - sv->scroll;
        }
        else
        {
            BeginHorizontal(r.x - sv->scroll, r.y, r.width);
            sv->contentStart = r.x - sv->scroll;
        }

        return true;
    }

    void EndScrollView()
    {
        Layout* l = &layoutStack[layoutTop];
        ScrollView* sv = &scrollStack[scrollTop];

        if (sv->axis == UI_SCROLL_VERTICAL)
        {
            sv->contentSize = l->cursorY - sv->contentStart;
        }
        else
        {
            sv->contentSize = l->cursorX - sv->contentStart;
        }

        EndLayout();
        EndScissorMode();

        float viewSize = (sv->axis == UI_SCROLL_VERTICAL)
            ? sv->viewRect.height
            : sv->viewRect.width;

        float maxScroll = sv->contentSize - viewSize;
        if (maxScroll < 0) maxScroll = 0;

        if (sv->scroll > maxScroll)
            sv->scroll = maxScroll;

        *(sv->externalScroll) = sv->scroll;

        //DrawRectangleLinesEx(sv->viewRect, 1, DARKGRAY);

        scrollTop--;
    }

#endif // MINIUI_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // MINIUI_H