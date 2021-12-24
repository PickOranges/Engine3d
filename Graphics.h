#pragma once
#include "Win.h"
#include <d3d11.h>
#include <vector>
#include "ExceptionBase.h"

class Graphics
{
public:
	class GHrException : public HrException {
	public:
		GHrException(int line, const char* file, HRESULT hr) noexcept;
		const char* GetType() const noexcept override;
	};
	class DeviceRemovedException : public GHrException
	{
	public:
		const char* GetType() const noexcept override;
	//private:
	//	std::string reason;
	};

public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;
};

