#include "Win.h"
#include "Window.h"
#include <iostream>



int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	try{
		Window wnd(800, 300, "Test Window class with an instance");
		
		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// check if GetMessage call itself borked
		if (gResult == -1)
		{
			//return -1;
			throw HWND_LAST_EXCEPT();
		}

		// wParam here is the value passed to PostQuitMessage
		return msg.wParam;
	}


	catch(const ExceptionBase& e){
		//MessageBox(nullptr, convchar("aaaaaaaaaaaaaaaaa"), convchar("Window Exception mually printed"), MB_OK | MB_ICONEXCLAMATION);  // This one works for pop-up window!!
		//MessageBox(nullptr, convchar(e.what()), convchar(e.GetType()), MB_OK | MB_ICONEXCLAMATION);
		//MessageBox(nullptr, reinterpret_cast<const wchar_t*>(e.what()), convchar(e.GetType()), MB_OK | MB_ICONEXCLAMATION); // This also pop-up but e.what() is trash.
		//const wchar_t* wwhat = e.what();
		MessageBox(nullptr, (LPWSTR)(e.what()), convchar(e.GetType()), MB_OK | MB_ICONEXCLAMATION);  // This also pop-up but e.what() is trash.
	}
	catch(const std::exception& e) {
		MessageBox(nullptr, (LPCWSTR)(e.what()), convchar("C++ Standard Exception"), MB_OK | MB_ICONEXCLAMATION);
	}
	catch(...) {
		MessageBox(nullptr, convchar("No details available"), convchar("Unknown Exception"), MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}