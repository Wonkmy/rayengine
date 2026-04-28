#include "EnemyEntity.h"


EnemyEntity::EnemyEntity() {
}

void EnemyEntity::OnStart() {
    this->angle = 180.0f;
    this->active = true;
    this->drawBoundingBox = true;
    this->position = Vector2{ 0.0f, 0.0f };
    this->collider = Collider{ boundingBox, false, false };
	//读取config.ini文件中的血量值
    int enemyBlood = GetIniInt("assets/config.ini", "EnemyTotalBlood", 0);
    if (enemyBlood > 0) {
        this->totalBlood = enemyBlood;
        this->currentBlood = enemyBlood;
	}
}

void EnemyEntity::OnUpdate() {
    if (!active)return;
    this->position.y += 1.0f;
    UpdateBoundingBox();

    if (this->position.y >= GetScreenHeight() * 0.5f) {
        RemoveEntity(this->id); // 当移出屏幕时，销毁
    }
}

void EnemyEntity::OnDraw() {
    DrawTexturePro(this->texture,
        Rectangle{
        0, 0, (float)this->texture.width, (float)this->texture.height
        },
        Rectangle{
            this->position.x, this->position.y, this->texture.width * GAME_SCALE, this->texture.height * GAME_SCALE
        },
        Vector2{
            this->texture.width / 2 * GAME_SCALE, this->texture.height / 2 * GAME_SCALE
        },
        this->angle, WHITE);
    if (this->drawBoundingBox) {
        DrawBoundingBox(boundingBox, RED);
    }

    DrawBloodBar();
}

void EnemyEntity::OnGUI() {
    
}

void EnemyEntity::DrawBloodBar() {
	DrawRectangle(this->position.x - 50, this->position.y - 60, 100 * (this->currentBlood / (float)this->totalBlood), 10, RED);
	DrawText(this->name.c_str(), this->position.x - 50, this->position.y - 75, 10, WHITE);
}

void EnemyEntity::TakeDamage(int damage) {
    this->currentBlood -= damage;
    if (this->currentBlood <= 0) {
        this->currentBlood = 0;
        // 在这里可以添加敌人死亡的逻辑，例如播放动画、掉落物品等
        RemoveEntity(this->id); // 销毁敌人实体
    }
}

void EnemyEntity::OnDispose() {
    this->active = false;
    //UnloadTexture(this->texture);
}

EnemyEntity::~EnemyEntity() {
}