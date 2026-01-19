#define _CRT_SECURE_NO_WARNINGS
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include <string.h>
#include <windows.h>
#include <stdio.h>
LUAI_FUNC int onload(lua_State* L);
LUAI_FUNC int onLoadImage(lua_State* L);
LUAI_FUNC int loop(lua_State* L);
LUAI_FUNC int unload(lua_State* L);