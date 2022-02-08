#pragma once
#include "Window.h"
#include "TimerWrapper.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include <set>

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame(); // contain top-level game logic.
	void SpawnSimulationWindow() noexcept;
	void SpawnBoxWindowManagerWindow() noexcept;  // For box-selection-dropdown menu.
	void SpawnBoxWindows() noexcept; // For changing the material params of the selected box.
private:
	ImguiManager imgui;
	Window wnd;
	TimerWrapper timer;
	Camera cam;
	PointLight light;
	std::vector<class Box*> boxes;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 180;
	float speed_factor = 1.0f;
	std::optional<int> comboBoxIndex;
	std::set<int> boxControlIds;
};

