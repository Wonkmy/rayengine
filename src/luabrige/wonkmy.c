//#include "lualib.h"
//#include "lauxlib.h"

//int main(int argc, char** argv) {
//	lua_State* L = luaL_newstate();
//	luaL_openlibs(L);
//	if (luaL_dostring(L, "print('Hello, World lua!')")) {
//		const char* error = lua_tostring(L, -1);
//		fprintf(stderr, "Error: %s\n", error);
//		lua_pop(L, 1);
//	}
//	lua_close(L);
//	return 0;
//}