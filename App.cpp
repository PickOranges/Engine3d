#include "App.h"
//#include "Melon.h"
//#include "Pyramid.h"
#include "Box.h"
#include <memory>
#include <algorithm>
#include "SimpleMath.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"


App::App()
	: 
	wnd(800, 600, "Test App Class Obj"),
	light(wnd.Gfx())
{
	class Factory
	{
	public:
		Factory(Graphics& gfx)
			:
			gfx(gfx)
		{}
		std::unique_ptr<Drawable> operator()()
		{
			//switch (typedist(rng))
			//{
			//case 0:
			//	return std::make_unique<Pyramid>(
			//		gfx, rng, adist, ddist,
			//		odist, rdist
			//		);
			//case 1:
			//	return std::make_unique<Box>(
			//		gfx, rng, adist, ddist,
			//		odist, rdist, bdist
			//		);
			//case 2:
			//	return std::make_unique<Melon>(
			//		gfx, rng, adist, ddist,
			//		odist, rdist, longdist, latdist
			//		);
			//default:
			//	assert(false && "bad drawable type in factory");
			//	return {};
			

			
			//const DirectX::XMFLOAT3 mat = { cdist(rng),cdist(rng),cdist(rng) };
			const DirectX::XMFLOAT3 mat = { 0.5f, 0.5f, 1.0f };

			return std::make_unique<Box>(
				gfx, rng, adist, ddist,
				odist, rdist, bdist, mat
				);
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_real_distribution<float> cdist{ 0.0f,1.0f };

		std::uniform_int_distribution<int> latdist{ 5,20 };
		std::uniform_int_distribution<int> longdist{ 10,40 };
		std::uniform_int_distribution<int> typedist{ 0,2 };
	};

	Factory f(wnd.Gfx());
	drawables.reserve(nDrawables);
	std::generate_n(std::back_inserter(drawables), nDrawables, f);

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

	for (auto& d : drawables)
	{
		d->Update(wnd.kbd.KeyIsPressed(VK_SPACE) ? 0.0f : dt);
		d->Draw(wnd.Gfx());
	}
	light.Draw(wnd.Gfx()); // draw the light source lastely.



	if(ImGui::Begin("Simulation Speed"))
	{
		//ImGui::ShowDemoWindow(&show_demo_window);
		ImGui::SliderFloat("Speed Factor",&speed_factor,0.0f,6.0f);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Status: %s", wnd.kbd.KeyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING(Hole the SPACE to pause)");
	}
	ImGui::End();

	// ImGui: add slidebars to control the camera and point light source params.
	cam.SpawnControlWindow();
	light.SpawnControlWindow(); 
	

	// present
	wnd.Gfx().EndFrame();
}
