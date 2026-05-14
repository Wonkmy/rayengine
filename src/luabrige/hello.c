#include "lualib.h"
#include "lauxlib.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

//int main(int argc, char** argv) {
//    char search_path[MAX_PATH];
//    snprintf(search_path, MAX_PATH, "%s\\*", "testgame");
//
//    WIN32_FIND_DATAA fd;
//    HANDLE hFind = FindFirstFileA(search_path, &fd);
//    if (hFind == INVALID_HANDLE_VALUE) {
//        printf("无法打开文件夹: %s\n", "testgame");
//        return 1;
//    }
//
//    int found = 0;
//    do {
//        // 只判断文件（不判断子文件夹），可以根据需求调整
//        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
//            if (strcmp(fd.cFileName, "main.lua") == 0) {
//                printf("找到目标文件: %s\\%s\n", "testgame", fd.cFileName);
//                found = 1;
//                break;
//            }
//        }
//    } while (FindNextFileA(hFind, &fd));
//
//    FindClose(hFind);
//
//    if (!found) {
//        printf("未找到目标文件: %s\n", fd.cFileName);
//    }
//
//    char fullpath[MAX_PATH] = { 0 };
//    snprintf(fullpath, MAX_PATH, "%s\\%s", "testgame", fd.cFileName);
//
//	lua_State* L = luaL_newstate();
//	luaL_openlibs(L);
//    if (luaL_dofile(L, fullpath)) {
//        const char* err = lua_tostring(L, -1);
//        printf("Error: %s\n", err);
//        lua_pop(L, 1);
//    }
//	lua_close(L);
//    return 0;
//}