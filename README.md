# rayengine

A Simple to use 2D/3D Game Engine!





//Vector2 p;

//Vector2 pos;

//bool showMessageBox = false;

//void MainOnStart() {

//	p.x = 0;

//	p.y = 0;

//	pos = screen(p);

//

//	lua\_rawgeti(engine.L, LUA\_REGISTRYINDEX, engine.load\_ref);

//	lua\_pcall(engine.L, 0, 0, 0);

//}

//void MainOnUpdate() {

//	lua\_rawgeti(engine.L, LUA\_REGISTRYINDEX, engine.update\_ref);

//	lua\_pcall(engine.L, 0, 0, 0);

//}

//void MainOnDraw() {

//	DrawFPS(GetScreenWidth() - 95, 10);

//	lua\_rawgeti(engine.L, LUA\_REGISTRYINDEX, engine.draw\_ref);

//	lua\_pcall(engine.L, 0, 0, 0);

//	if (GuiButton((Rectangle) { screen(p).x, screen(p).y, 120, 30 }, "#191#Show Message")) showMessageBox = true;

//

//	if (showMessageBox)

//	{

//		int result = GuiMessageBox((Rectangle) { 85, 70, 250, 100 },

//			"#191#Message Box", "Hi! This is a message!", "Nice;Cool");

//

//		if (result >= 0) showMessageBox = false;

//	}

//}

//void MainOnDispose() {

//	lua\_rawgeti(engine.L, LUA\_REGISTRYINDEX, engine.dispose\_ref);

//	lua\_pcall(engine.L, 0, 0, 0);

//

//	lua\_close(engine.L);

//}

//#endif



























// lua状态机相关

//#ifdef USE\_LUA

//	lua\_State\* L = luaL\_newstate();// 创建一个新的lua解释器状态机

//	luaL\_openlibs(L);// 加载lua标准库

//	luaL\_newmetatable(L, "TextureMetaTable");// 创建Texture元表用来管理全局纹理

//	luaL\_dofile(L, argv\[0]);// 执行lua文件

//	lua\_getglobal(L, "onLoad");

//	if (luaL\_dofile(L, argv\[1])) {

//		fprintf(stderr, "Error:%s\\n", lua\_tostring(L, -1));

//	}

//	// 获取load函数引用

//	lua\_getglobal(L, "load");

//	engine.load\_ref = luaL\_ref(L, LUA\_REGISTRYINDEX);

//

//	// 获取update函数引用

//	lua\_getglobal(L, "update");

//	engine.update\_ref = luaL\_ref(L, LUA\_REGISTRYINDEX);

//

//	// 获取draw函数引用

//	lua\_getglobal(L, "draw");

//	engine.draw\_ref = luaL\_ref(L, LUA\_REGISTRYINDEX);

//

//	// 获取dispose函数引用

//	lua\_getglobal(L, "dispose");

//	engine.dispose\_ref = luaL\_ref(L, LUA\_REGISTRYINDEX);

//

//	// 将lua\_State指针赋值给游戏引擎

//	engine.L = L;

//

//	// 设置游戏引擎的各个回调函数

//	engine.load = \&load;

//	engine.update = \&update;

//	engine.draw = \&draw;

//	engine.dispose = \&dispose;

//

//	SetTargetFPS(FPS);

//

//	// 创建并运行游戏应用

//    int r = createGameApp(\&engine, GAME\_WIDTH, GAME\_HEIGHT, "My Game");

//    return r;

//#endif





// 自然语言脚本解析器主入口文件

//#define DSL\_IMPLEMENTATION

//#include "dsl\_parser.h"

//

//int main(void)

//{

//    AST ast;

//

//    /\* 1. 解析脚本 \*/

//    dsl\_parse\_file("game.dsl", \&ast);

//

//    /\* 2. 打印 AST（验证是否解析成功） \*/

//    dsl\_ast\_dump(\&ast);

//

//    /\* 3. 释放内存 \*/

//    dsl\_ast\_free(\&ast);

//	system("pause");

//    return 0;

//}

