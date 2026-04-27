#include "game.h"
 //入口
int main(int args, const char* argv[])
{
	Actor newGame = NewGame();
	initGame();
	RunGame(&newGame);
	return 0;
}