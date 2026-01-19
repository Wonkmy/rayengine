#include "Player.h"

// 真正的 init 实现（私有）
void Player_Init_Impl(Player* self)
{
    self->X = 100;
    self->Y = 200;
    self->mainTexture = LoadTexture("player.png");
}

// 构造函数
void player_Init(Player* player)
{
    player->init = Player_Init_Impl;
}

void player_Draw(Player* self)
{
    DrawTexture(self->mainTexture, self->X, self->Y, WHITE);
}