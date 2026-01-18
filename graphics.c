#define ltablib_c
#define LUA_LIB

#include "lprefix.h"
#include <limits.h>
#include <stddef.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "graphics.h"

static int loadtexture(lua_State* L) {
	const char* filename = luaL_checkstring(L, 1);
	Texture2D texture = LoadTexture(filename);
	if(texture.id == 0) {
		return luaL_error(L, "Failed to load texture: %s", filename);
	}

	Texture2D* tex = (Texture2D*)lua_newuserdata(L, sizeof(Texture2D));
	*tex = texture;

	luaL_getmetatable(L, "TextureMetaTable");
	lua_setmetatable(L, -2);
	return 1;
}
static int drawtext(lua_State* L) {
	const char* fromname = luaL_checkstring(L, 1);
	DrawText(fromname, 100, 100, 20, RED);
	
	return 0;
}

static int drawtexture(lua_State* L) {
	// 获取传入的Texture userdata
	Texture2D* tex = (Texture2D*)luaL_checkudata(L, 1, "TextureMetaTable");
	Texture2D texture = *tex;
	int x = luaL_checkinteger(L, 2);
	int y = luaL_checkinteger(L, 3);
	DrawTexture(texture, x, y, WHITE);
	return 0;
}

static int texture_gc(lua_State* L)
{
	lua_setfield(L, -2, "__gc");
	lua_pop(L, 1);
	Texture2D* tex = (Texture2D*)luaL_checkudata(L, 1, "TextureMetaTable");
	if (tex->id != 0)
	{
		UnloadTexture(*tex);
		tex->id = 0;
	}
	return 0;
}


static const luaL_Reg tab_funcs[] = {
  {"drawtext",drawtext},// 这里引号中的drawtext就是lua中使用的函数名
  {"createTexture",loadtexture},
  {"drawTexture",drawtexture},
  {"disposeTexture",texture_gc},
  {NULL, NULL}
};


LUAMOD_API int luaopen_graphics(lua_State* L) {
	luaL_newlib(L, tab_funcs);
	return 1;
}