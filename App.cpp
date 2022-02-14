#include "App.h"
#include "Pyramid.h"
#include "Box.h"
#include "Cylinder.h"
#include <memory>
#include <algorithm>
#include "SimpleMath.h"


App::App()
	: 
	wnd(800, 600, "Test App Class Obj"),
	light(wnd.Gfx())
{
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
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
	light.Draw(wnd.Gfx()); // draw the light source lastely.
	nano.Draw(wnd.Gfx());
	
	// imgui windows
	cam.SpawnControlWindow();
	light.SpawnControlWindow();

	// present
	wnd.Gfx().EndFrame();
}