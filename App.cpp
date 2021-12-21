#include "App.h"
#include <iomanip>

App::App()
	: wnd(800, 600, "Test App Class Obj")
{
}

int App::Go()
{
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		// TranslateMessage will post auxilliary WM_CHAR messages from key msgs
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (!wnd.mouse.IsEmpty()) {
			while (!wnd.mouse.IsEmpty()) {
				const auto e = wnd.mouse.Read();
				std::ostringstream oss;
				oss << "Mouse Position: (" << e.GetPosX() << "," << e.GetPosY() << ")" << std::endl;
				wnd.SetTitle(oss.str());
				if (e.GetType() == Mouse::Event::Type::Move) {
					std::ostringstream oss;
					oss << "Mouse Position: (" << e.GetPosX() << "," << e.GetPosY() << ")" << std::endl;
					wnd.SetTitle(oss.str());
				}
			}
		}

		// check if GetMessage call itself borked
		if (gResult == -1)
		{
			throw HWND_LAST_EXCEPT();
		}

		return msg.wParam;
	}
}

void App::DoFrame()
{
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " <<std::setprecision(1)<<std::fixed<< t << std::endl;
	wnd.SetTitle(oss.str());
}

