#pragma once

#define HWND_EXCEPT( hr ) HrException( __LINE__,__FILE__,(hr) )
#define HWND_LAST_EXCEPT() HrException( __LINE__,__FILE__,GetLastError() )
#define HWND_NOGFX_EXCEPT() Window::NoGfxException( __LINE__,__FILE__ )