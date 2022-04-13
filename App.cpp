#include "App.h"
#include "imgui/imgui.h"
#include "Testing.h"

namespace dx = DirectX;

App::App()
	: 
	wnd(1280, 720, "Test App Class Obj"),
	light(wnd.Gfx())
{
	TestMaterialSystemLoading(wnd.Gfx());
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 400.0f));
	cube.SetPos({ 4.0f,0.0f,0.0f });
	cube2.SetPos({ 0.0f,4.0f,0.0f });

	{
		std::string path = "models\\brick_wall\\brick_wall.obj";
		Assimp::Importer imp;
		const auto pScene = imp.ReadFile(path,
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_ConvertToLeftHanded |
			aiProcess_GenNormals |
			aiProcess_CalcTangentSpace
		);
		Material mat{ wnd.Gfx(),*pScene->mMaterials[1],path };
		pLoaded = std::make_unique<Mesh>(wnd.Gfx(), mat, *pScene->mMeshes[0]);
	}
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
	wnd.Gfx().SetCamera(cam.GetMatrix());
	light.Bind(wnd.Gfx(), cam.GetMatrix());


	light.Submit(fc);
	//cube.Submit(fc);
	//cube2.Submit(fc);
	pLoaded->Submit(fc, DirectX::XMMatrixIdentity());
	fc.Execute(wnd.Gfx());


	// Handles the messages from mouse and keyboard.
	while (const auto e = wnd.kbd.ReadKey())	
	{
		if(!e->IsPress())
		{
			continue;
		}
		switch(e->GetCode())
		{
		case VK_ESCAPE:
			if (wnd.CursorEnabled())
			{
				wnd.DisableCursor();
				wnd.mouse.EnableRaw();
			}
			else
			{
				wnd.EnableCursor();
				wnd.mouse.DisableRaw();
			}
			break;
		case VK_F1:
			showDemoWindow = true;
			break;
		}
	}
	if (!wnd.CursorEnabled())
	{
		if (wnd.kbd.KeyIsPressed('W'))
		{
			cam.Translate({ 0.0f,0.0f,dt });
		}
		if (wnd.kbd.KeyIsPressed('A'))
		{
			cam.Translate({ -dt,0.0f,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			cam.Translate({ 0.0f,0.0f,-dt });
		}
		if (wnd.kbd.KeyIsPressed('D'))
		{
			cam.Translate({ dt,0.0f,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('R'))
		{
			cam.Translate({ 0.0f,dt,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('F'))
		{
			cam.Translate({ 0.0f,-dt,0.0f });
		}
	}
	while (const auto delta = wnd.mouse.ReadRawDelta())
	{
		if (!wnd.CursorEnabled())
		{
			cam.Rotate((float)delta->x, (float)delta->y);
		}
	}

	
	// imgui windows
	cam.SpawnControlWindow();
	light.SpawnControlWindow();
	ShowImguiDemoWindow();
	//sponza.ShowWindow(wnd.Gfx(), "Sponza");
	cube.SpawnControlWindow(wnd.Gfx(), "Cube 1");
	cube2.SpawnControlWindow(wnd.Gfx(), "Cube 2");


	// present
	wnd.Gfx().EndFrame();

	fc.Reset();
}

void App::ShowImguiDemoWindow()
{
	if (showDemoWindow) {
		ImGui::ShowDemoWindow(&showDemoWindow);
	}
}
