#include <Windows.h> 

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

int CALLBACK WinMain(
	HINSTANCE hInstance,	 
	HINSTANCE hPrevInstance, 
	LPSTR IpCmdLine, 
	int nCmdShow  
) {
	// register window class
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc; 
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;

	const char cname[]  = "hw3dbutts";
	size_t len = strlen(cname) + 1; 
	wchar_t pClassName[20];
	mbstowcs_s(&len,pClassName,20,cname,100);
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);

	// create window instance
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
	BOOL gResult;
	while((gResult=GetMessage(&msg,nullptr,0,0))>0){
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}

	if (gResult==-1) {
		return -1;
	}
	else {
		return msg.wParam; 
	}
}