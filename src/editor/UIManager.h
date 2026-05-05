#pragma once
#include "imgui.h"
#include "raylib.h"

class UIManager
{
public:
	static UIManager* sm_pSharedUIManager;
	Texture2D _text;
	void Init();
	void CreatePanel();
	void Test();
};
