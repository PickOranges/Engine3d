#pragma once
#include "Window.h"
#include "TimerWrapper.h"

class App
{
public:
	App();
	int Go();
private:
	void DoFrame(); // contain top-level game logic.
private:
	Window wnd;
	TimerWrapper timer;
};

