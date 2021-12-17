#include "Win.h"
#include <string>
#include <sstream>


// customized window's procedure.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_KEYDOWN:
		if(wParam=='F')
			SetWindowText(hWnd, convchar("Respects"));
		break;
	case WM_KEYUP:
		if (wParam == 'F')
			SetWindowText(hWnd, convchar("Dangerfield"));
		break;
	case WM_CHAR:
		{
			static std::string title;
			title.push_back((char)wParam);
			SetWindowText(hWnd, convchar(const_cast<const char*>(title.c_str())));
		}		
		break;
	case WM_LBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			std::ostringstream oss;
			oss << "(" << pt.x << ", " << pt.y << ")";
			SetWindowText(hWnd, convchar(oss.str().c_str()));
		}
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
	LPCWSTR pClassName = convchar("hw3dclass");
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);

	// create window instance
	HWND hWnd = CreateWindowExW(
		0, pClassName, 
		convchar("Happy Hard Window"),
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