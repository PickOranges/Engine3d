#pragma once
#include "Window.h"
#include "TimerWrapper.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include <set>
#include "Model.h"
#include "TestCube.h"
#pragma once
#include "Window.h"
#include "TimerWrapper.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include "TestPlane.h"
#include "TestCube.h"
#include "Model.h"
#include <set>
#include "Stencil.h"
#include "FrameCommander.h"
#include "Material.h"


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

	FrameCommander fc;


	PointLight light;
	float speed_factor = 1.0f;
	bool showDemoWindow = false;


	Model sponza{ wnd.Gfx(),"models\\sponza\\sponza.obj",1.0f/20.f };
	//TestCube cube{ wnd.Gfx(),4.0f }; 
	//TestCube cube2{ wnd.Gfx(),4.0f };
	//std::unique_ptr<Mesh> pLoaded;
};

