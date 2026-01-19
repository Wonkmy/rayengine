#include "game.h"
typedef struct Player {
	int X;
	int Y;
	Texture2D mainTexture;
	void (*init)();
} Player;