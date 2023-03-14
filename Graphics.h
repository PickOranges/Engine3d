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


namespace Bind
{
	class Bindable;
	class RenderTarget;
}

namespace wrl = Microsoft::WRL;


class Graphics
{
	friend class GraphicsResource;

public:
	class GHrException : public HrException {
	public:
		GHrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept; 

	private:
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
	Graphics(HWND hWnd, int width, int height);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();
	void EndFrame();
	void BeginFrame(float red, float green, float blue) noexcept;
	void DrawIndexed(UINT count) noexcept(!IS_DEBUG); 

	void SetCamera(DirectX::FXMMATRIX cam) noexcept;
	DirectX::XMMATRIX GetCamera() const noexcept;
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;


	void EnableImgui() noexcept;
	void DisableImgui() noexcept;
	bool IsImguiEnabled() const noexcept;


	std::shared_ptr<Bind::RenderTarget> GetTarget();

	UINT GetWidth() const noexcept;
	UINT GetHeight() const noexcept;
private:
	bool imguiEnabled = true;
	DirectX::XMMATRIX camera;
	DirectX::XMMATRIX projection;

	UINT width;
	UINT height;
#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif
	wrl::ComPtr<ID3D11Device> pDevice;
	wrl::ComPtr<IDXGISwapChain> pSwap;
	wrl::ComPtr<ID3D11DeviceContext> pContext;
	std::shared_ptr<Bind::RenderTarget> pTarget;
};

