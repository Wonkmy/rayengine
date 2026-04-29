#pragma once
#include "imgui.h"
class UIManager
{
public:
	static UIManager* sm_pSharedUIManager;
	void CreatePanel();
};
