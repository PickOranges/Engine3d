#pragma once
#include "Window.h"
#include "TimerWrapper.h"

class App
{
public:
	App();
	int Go();
	~App();
private:
	void DoFrame(); // contain top-level game logic.
private:
	Window wnd;
	TimerWrapper timer;
	std::vector<std::unique_ptr<class Box>> boxes;
};

