#pragma once
#include "Window.h"
#include "TimerWrapper.h"
#include "ImguiManager.h"
#include "CameraContainer.h"
#include "PointLight.h"
#include "TestCube.h"
#include "Model.h"
#include "BlurOutlineRenderGraph.h"
#include "SimpleMath.h"



class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame(float dt); // contain top-level game logic.
	void HandleInput(float dt);
	void ShowImguiDemoWindow();
private:
	bool showDemoWindow = false;
	ImguiManager imgui;
	Window wnd;
	Rgph::BlurOutlineRenderGraph  rg{ wnd.Gfx() };



	TimerWrapper timer;
	float speed_factor = 1.0f;
	CameraContainer cameras;



	PointLight light;
	TestCube cube{ wnd.Gfx(),4.0f }; 
	TestCube cube2{ wnd.Gfx(),4.0f };
	Model sponza{ wnd.Gfx(),"models\\sponza\\sponza.obj",1.0f / 20.f };
};

