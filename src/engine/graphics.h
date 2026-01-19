#include "game.h"
int drawtext(lua_State* L);
static int loadtexture(lua_State* L);
static int drawtexture(lua_State* L);
static int texture_gc(lua_State* L);