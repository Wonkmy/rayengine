#include "EnemyEntity.h"

int totalBlood = 100;
int currentBlood = 100;

EnemyEntity::EnemyEntity() {
}

void EnemyEntity::OnStart() {
    this->angle = 0.0f;
    this->active = true;
    this->drawBoundingBox = false;
    this->position = Vector2{ 0.0f, 0.0f };

	//读取config.ini文件中的血量值
    int enemyBlood = GetIniInt("assets/config.ini", "EnemyTotalBlood", 0);
    if (enemyBlood > 0) {
        totalBlood = enemyBlood;
        currentBlood = enemyBlood;
	}
}

void EnemyEntity::OnUpdate() {
    UpdateBoundingBox();
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
	DrawRectangle(this->position.x - 50, this->position.y - 120, 100 * (currentBlood / (float)totalBlood), 10, RED);
}

void EnemyEntity::TakeDamage(int damage) {
    currentBlood -= damage;
    if (currentBlood <= 0) {
        currentBlood = 0;
        // 在这里可以添加敌人死亡的逻辑，例如播放动画、掉落物品等
        RemoveEntity(this->id); // 销毁敌人实体
    }
}

void EnemyEntity::OnDispose() {
    this->active = false;
    UnloadTexture(this->texture);
}

EnemyEntity::~EnemyEntity() {
}