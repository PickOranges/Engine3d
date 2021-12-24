#include "DxgiInfoManager.h"
#include "Window.h"
#include "Graphics.h"
#include <dxgidebug.h>
#include <memory>

#pragma comment(lib, "dxguid.lib")

//#define GFX_THROW_NOINFO(hrcall) if( FAILED( hr = (hrcall) ) ) throw Graphics::HrException( __LINE__,__FILE__,hr )

DxgiInfoManager::DxgiInfoManager()
{
	// define function signature of DXGIGetDebugInterface
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

	// load the dll that contains the function DXGIGetDebugInterface
	const auto hModDxgiDebug = LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	if (hModDxgiDebug == nullptr) {
		throw HWND_LAST_EXCEPT();
	}

	// get address of DXGIGetDebugInterface in dll
	const auto DxgiGetDebugInterface= reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface")));
	if (DxgiGetDebugInterface == nullptr) {
		throw HWND_LAST_EXCEPT();
	}

//	HRESULT hr;
//	GFX_THROW_NOINFO(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), reinterpret_cast<void**>(&pDxgiInfoQueue)));
}
