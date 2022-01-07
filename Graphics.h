#pragma once
#include "Win.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include "ExceptionBase.h"
#include "DxgiInfoManager.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include <random>
#include <vector>

namespace wrl = Microsoft::WRL;


class Graphics
{
	friend class Bindable;

public:
	class GHrException : public HrException {
	public:
		GHrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept; 

	private:
		//HRESULT hr;
		std::string info;
	};
	class DeviceRemovedException : public GHrException
	{
	public:
		DeviceRemovedException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};
	class InfoException : public Exception
	{
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};

public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics()=default;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void DrawIndexed(UINT count) noexcept(!IS_DEBUG); 
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;

private:
	DirectX::XMMATRIX projection;
#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif
	wrl::ComPtr<ID3D11Device> pDevice;
	wrl::ComPtr<IDXGISwapChain> pSwap;
	wrl::ComPtr<ID3D11DeviceContext> pContext;
	wrl::ComPtr<ID3D11RenderTargetView> pTarget;
	wrl::ComPtr<ID3D11DepthStencilView> pDSV;
};

