#include <Windows.h>  // 1. You need to include it!

// customized window's procedure.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}

//int main() {
//	return 0;
//}
// 2. the entry point must have a name called WinMain! Not main()!


// CALLBACK: uses different calling convention that c++ call, i.e. stat call. Windows API always use it.
int CALLBACK WinMain(
	HINSTANCE hInstance,	 // Ignore.(Check the documentation for details.)
	HINSTANCE hPrevInstance, // Always NULL. Ignore it.
	LPSTR IpCmdLine, // Receives the command line when you use single string.
	int nCmdShow  // Decides how the window should be shown when you created it.
) {
	// register window class
	// This is a normal way in DX.
	// Create a config structure, and then pass it to the creation function.
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	//wc.lpfnWndProc = DefWindowProc; // default procedure, no specific dealing with your window.
	wc.lpfnWndProc = WndProc; // when we close the window, the dubugger will also be closed.
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;

	// remember this convension, very useful.
	const char cname[]  = "hw3dbutts";
	size_t len = strlen(cname) + 1; // plus 1: the /0.
	wchar_t pClassName[20];
	//std::mbstowcs(pClassName,cname,len);
	mbstowcs_s(&len,pClassName,20,cname,100);
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);

	// create window instance
	// The function will return a handle of this window.
	const char* cwindowname= "Happy Hard Window";
	wchar_t pWindowName[50];
	size_t sz = strlen(cwindowname) + 1;
	mbstowcs_s(&sz, pWindowName, 50, cwindowname, 100);

	HWND hWnd = CreateWindowExW(
		0, pClassName, 
		pWindowName,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200,200,640,480,
		nullptr,nullptr,hInstance,nullptr
	);

	// show the window
	ShowWindow(hWnd,SW_SHOW);


	// message pump
	MSG msg;
	BOOL gResult; // BOOL is actually NOT a bool, but a int. This is for exception handling.
	//while (true);
	//while (GetMessage(&msg,nullptr,0,0)>0) {
	while((gResult=GetMessage(&msg,nullptr,0,0))>0){
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}

	if (gResult==-1) {
		return -1;
	}
	else {
		return msg.wParam; // This will return the quit message above, ie. 69. You can see this code in output when you close the winfdow.
	}
}