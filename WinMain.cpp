#include "App.h"



int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	try{
		//throw 890809; // these two lines are used for test of exception pop-up window.
		//throw std::runtime_error("aaaaaaaaaa");
		return App{}.Go();
	}
	catch(const ExceptionBase& e){
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION); 
	}
	catch(const std::exception& e) {
		//MessageBox(nullptr, (LPCWSTR)(e.what()), convchar("C++ Standard Exception"), MB_OK | MB_ICONEXCLAMATION); // used before change the default character width
		MessageBox(nullptr, e.what(), "C++ Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch(...) {
		//MessageBox(nullptr, convchar("No details available"), convchar("Unknown Exception"), MB_OK | MB_ICONEXCLAMATION); // used before change the default character width
		MessageBox(nullptr, "No details available.", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}