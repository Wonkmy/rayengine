/*
    core_js_equivalent.c

    严格等价还原最初的 JS 逻辑
    不包含任何渲染 / 光照 / 面处理
*/

#include <stdio.h>
#include "game.h"
#include <math.h>


Vector3 translate_z(Vector3 v, float dz)
{
    Vector3 r;
    r.x = v.x;
    r.y = v.y;
    r.z = v.z + dz;
    return r;
}

Vector3 rotate_xz(Vector3 v, float angle)
{
    float c = cos(angle);
    float s = sin(angle);

    Vector3 r;
    r.x = v.x * c - v.z * s;
    r.y = v.y;
    r.z = v.x * s + v.z * c;
    return r;
}

Vector2 project(Vector3 v)
{
    Vector2 r;
    r.x = v.x / v.z;
    r.y = v.y / v.z;
    return r;
}

Vector2 screen(Vector2 p)
{
    Vector2 r;
    r.x = (p.x + 1.0f) * 0.5f * GAME_WIDTH;
    r.y = (p.y + 1.0f) * 0.5f * GAME_HEIGHT;
    return r;
}

Vector3 vs[8] = {
    {-0.25,-0.25,-0.25}, { 0.25,-0.25,-0.25}, { 0.25, 0.25,-0.25}, {-0.25, 0.25,-0.25},
    {-0.25,-0.25, 0.25}, { 0.25,-0.25, 0.25}, { 0.25, 0.25, 0.25}, {-0.25, 0.25, 0.25}
};

int fs[6][4] = {
    {0,1,2,3},
    {4,5,6,7},
    {0,4,7,3},
    {1,5,6,2},
    {3,2,6,7},
    {0,1,5,4}
};
float _angle = 45;
void frame(float dz)
{
    float dt = 1.0f / FPS;
    //_angle = _angle + 0.0001;
    for (int fi = 0; fi < 6; ++fi)
    {
        for (int i = 0; i < 4; ++i)
        {
            Vector3 a = vs[fs[fi][i]];
            Vector3 b = vs[fs[fi][(i + 1) % 4]];

            Vector3 wa = translate_z(rotate_xz(a, _angle), dz);
            Vector3 wb = translate_z(rotate_xz(b, _angle), dz);

            Vector2 pa = screen(project(wa));
            Vector2 pb = screen(project(wb));

			DrawLine((int)pa.x, (int)pa.y, (int)pb.x, (int)pb.y, RED);
        }
    }
}
void Draw3D(float dz){
    /* 模拟一次 JS 的 frame() */
    frame(dz);
}
