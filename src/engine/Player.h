#include "game.h"
// Player.h
#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player Player;

struct Player {
    int X;
    int Y;
    Texture2D mainTexture;

    void (*init)(Player* self);
};

void player_Init(Player* player);
void player_Draw(Player* self);
#endif
