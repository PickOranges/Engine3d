#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WIN32_WINNT 0x0601
#include <sdkddkver.h>

#ifndef FULL_WINTARD
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
//#define NOMINMAX
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#endif



#define NOMINMAX
#define STRICT

#include <Windows.h>
//#include <stdlib.h>
//extern inline LPCWSTR convchar(const char* csrc) {
//	wchar_t* dest = new wchar_t[2000];
//	size_t len = strlen(csrc) + 1;
//	//mbstowcs_s(&len, dest, 100, csrc, 300);
//	mbstowcs(dest,csrc,len);
//	return dest;
//}
//
//extern inline char* convwchar(const wchar_t* wsrc) {
//	char* dest = new char[2000];
//	size_t len = wcslen(wsrc) + 1;
//	wcstombs(dest, wsrc, len);
//	return dest;
//}