#include "App.h"
#include <iomanip>
#include <thread>

App::App()
	: wnd(800, 600, "Test App Class Obj")
{
}

int App::Go()
{
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(2000ms);
	while (true) {
		if (const auto ecode = Window::ProcessMessages()) {
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " <<std::setprecision(1)<<std::fixed<< t << std::endl;
	wnd.SetTitle(oss.str());
}

