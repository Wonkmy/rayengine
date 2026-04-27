#include "raylib.h"
Model model;
Camera camera = { 0 };
Vector3 position = { 0.0f, 0.0f, 0.0f };
void MeshRenderOnStart() {
	model = LoadModel("assets/models/bridge.obj");
	Texture2D texture = LoadTexture("assets/models/bridge_diffuse.png");
	model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
	// 初始化摄像机
	camera.position = Vector3{ 0.0f, 20.0f, -10.0f };
	camera.target = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 60.0f;
	camera.projection = CAMERA_PERSPECTIVE;
}
void MeshRenderOnUpdate() {

}
void MeshRenderOnDraw() {
	BeginMode3D(camera);
		//DrawModel(model, position, 1.0f, WHITE);
		//DrawGrid(20, 10.0f);
		DrawTriangle(Vector2{ 0.0f, 0.0f}, Vector2{ 0, 1}, Vector2{ 1, 0}, RED);
	EndMode3D();
}
void MeshRenderOnDispose() {
	UnloadModel(model);
}