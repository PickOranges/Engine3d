#include <Windows.h> 

LPCWSTR convchar(const char* csrc) {
	wchar_t* dest=new wchar_t[50];
	size_t len = strlen(csrc) + 1;
	mbstowcs_s(&len,dest,50,csrc,100);
	return dest;
}

// customized window's procedure.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;

	case WM_KEYDOWN:
		SetWindowText(hWnd, convchar("Respects"));
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