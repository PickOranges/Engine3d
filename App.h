#pragma once
#include "Window.h"
#include "TimerWrapper.h"

class App
{
public:
	App();
	int Go();
private:
	void DoFrame();
private:
	Window wnd;
	TimerWrapper timer;
};

