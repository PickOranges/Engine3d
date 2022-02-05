#pragma once
#include "Window.h"
#include "TimerWrapper.h"
#include "ImguiManager.h"
#include "Camera.h"

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame(); // contain top-level game logic.
private:
	ImguiManager imgui;
	Window wnd;
	TimerWrapper timer;
	Camera cam;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 180;
	float speed_factor = 1.0f;
};

