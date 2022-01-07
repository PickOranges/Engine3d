#pragma once
#include "Win.h"
#include "ExceptionBase.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <optional>
#include <memory>

class Window
{
	class NoGfxException : public Exception
	{
	public:
		using Exception::Exception;
		const char* GetType() const noexcept override;
	};

	class WHrException : public HrException {
	public:
		WHrException(int line, const char* file, HRESULT hr) noexcept;
		const char* GetType() const noexcept override;
	//private:
	//	HRESULT hr;
	};

private:
	class WindowClass {
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		const char* wndClassName = "Test DX Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	}; 
public:
	Window(int width, int height, const char* name) noexcept(false);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessages();
	Graphics& Gfx();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
private:
	int width;
	int height;
	HWND hWnd;
public:
	Keyboard kbd;
	Mouse mouse;
	std::unique_ptr<Graphics> pGfx;
};
