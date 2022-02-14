#pragma once
#include "Window.h"
#include "TimerWrapper.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include <set>
#include "Mesh.h"

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame(); // contain top-level game logic.
	void ShowModelWindow();
private:
	ImguiManager imgui;
	Window wnd;
	TimerWrapper timer;
	Camera cam;
	PointLight light;
	float speed_factor = 1.0f;
	Model nano{ wnd.Gfx(),"models\\nanosuit.obj" };


	struct
	{
		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	} pos;
};

