#include "App.h"
#include <memory>
#include <algorithm>
#include "SimpleMath.h"
#include "imgui/imgui.h"


App::App()
	: 
	wnd(1280, 720, "Test App Class Obj"),
	light(wnd.Gfx())
{
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 40.0f));
}

int App::Go()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}

}

App::~App()
{}

void App::DoFrame()
{
	const auto dt = timer.Mark()*speed_factor;

	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);

	// Now update camera params every frame(Instead of updating just once in ctor when init App).
	wnd.Gfx().SetCamera(cam.GetMatrix());
	light.Bind(wnd.Gfx(), cam.GetMatrix());

	nano.Draw(wnd.Gfx());
	light.Draw(wnd.Gfx()); // draw the light source lastely.
	
	// imgui windows
	cam.SpawnControlWindow();
	light.SpawnControlWindow();
	ShowImguiDemoWindow();
	nano.ShowWindow();

	// present
	wnd.Gfx().EndFrame();
}

void App::ShowImguiDemoWindow()
{
	// Decouppling: separate the node tree control with App class(moved into Model class).
	// Note: Current window does NOT have actual functionality, i.e. you cannot actually control it.

}