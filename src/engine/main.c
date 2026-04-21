#include <math.h>
#include "game.h"
#include "lualib.h"
#include "lauxlib.h"
#include <stdio.h>
#include <stdlib.h>

#include "mainlayer.h"

 //游戏主入口文件
int main(int args, const char* argv[])
{
#ifdef USE_LUA
	lua_State* L = luaL_newstate();// 创建一个新的lua解释器状态机
	luaL_openlibs(L);// 加载lua标准库
	luaL_newmetatable(L, "TextureMetaTable");// 创建Texture元表用来管理全局纹理
	luaL_dofile(L, argv[0]);// 执行lua文件
	lua_getglobal(L, "onLoad");
	if (luaL_dofile(L, argv[1])) {
		fprintf(stderr, "Error:%s\n", lua_tostring(L, -1));
	}
	// 获取load函数引用
	lua_getglobal(L, "load");
	engine.load_ref = luaL_ref(L, LUA_REGISTRYINDEX);
	
	// 获取update函数引用
	lua_getglobal(L, "update");
	engine.update_ref = luaL_ref(L, LUA_REGISTRYINDEX);

	// 获取draw函数引用
	lua_getglobal(L, "draw");
	engine.draw_ref = luaL_ref(L, LUA_REGISTRYINDEX);

	// 获取dispose函数引用
	lua_getglobal(L, "dispose");
	engine.dispose_ref = luaL_ref(L, LUA_REGISTRYINDEX);

	// 将lua_State指针赋值给游戏引擎
	engine.L = L;

	// 设置游戏引擎的各个回调函数
	engine.load = &load;
	engine.update = &update;
	engine.draw = &draw;
	engine.dispose = &dispose;

	SetTargetFPS(FPS);

	// 创建并运行游戏应用
    int r = createGameApp(&engine, GAME_WIDTH, GAME_HEIGHT, "My Game");
    return r;
#endif

	InitWindow(GAME_WIDTH, GAME_HEIGHT, GAME_TITLE);
	MainOnStart();
	Camera camera = { 0 };
	camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; // Camera position
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };     // Camera looking at point
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 25.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(BLACK);
			MainOnUpdate();
			BeginMode3D(camera);
				MainOnDraw();
				DrawGrid(20, 10.0f);         // Draw a grid
			EndMode3D();
		EndDrawing();
	}
	MainOnDispose();
	CloseWindow();
	return 0;
}

// 自然语言脚本解析器主入口文件
//#define DSL_IMPLEMENTATION
//#include "dsl_parser.h"
//
//int main(void)
//{
//    AST ast;
//
//    /* 1. 解析脚本 */
//    dsl_parse_file("game.dsl", &ast);
//
//    /* 2. 打印 AST（验证是否解析成功） */
//    dsl_ast_dump(&ast);
//
//    /* 3. 释放内存 */
//    dsl_ast_free(&ast);
//	system("pause");
//    return 0;
//}