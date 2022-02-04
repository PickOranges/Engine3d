#pragma once
#include "Window.h"
#include "TimerWrapper.h"
#include "ImguiManager.h"

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
	std::vector<std::unique_ptr<class Drawable>> drawables;
	bool show_demo_window = true;
	static constexpr size_t nDrawables = 180;
	bool show_demo_window = true;
};

