#pragma once
#include "Window.h"
#include "TimerWrapper.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include <set>
#include "Mesh.h"
#include "TestPlane.h"


class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame(); // contain top-level game logic.
	void ShowImguiDemoWindow();
private:
	ImguiManager imgui;
	Window wnd;
	TimerWrapper timer;
	Camera cam;
	PointLight light;
	float speed_factor = 1.0f;
	//Model nano{ wnd.Gfx(),"models\\nano_textured\\nanosuit.obj" };
	//Model wall{ wnd.Gfx(),"Models\\brick_wall\\brick_wall.obj" };
	//TestPlane tp{ wnd.Gfx(),1.0 };
	bool showDemoWindow = false;
};

