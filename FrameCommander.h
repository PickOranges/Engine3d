#pragma once
#include <array>
#include "BindableBase.h"
#include "Graphics.h"
#include "Job.h"
#include "Pass.h"
#include "DepthStencil.h"
#include "RenderTarget.h"
#include "BlurPack.h"
#include <array>

class FrameCommander
{
public:
	FrameCommander(Graphics& gfx)
		:
		ds(gfx, gfx.GetWidth(), gfx.GetHeight()),
		rt1({ gfx,gfx.GetWidth() / downFactor,gfx.GetHeight() / downFactor }),
		rt2({ gfx,gfx.GetWidth() / downFactor,gfx.GetHeight() / downFactor }),
		blur(gfx, 7, 2.6f, "BlurOutline_PS.cso")
	{
		namespace dx = DirectX;

		// setup fullscreen geometry
		hw3d::VertexLayout lay;
		lay.Append(hw3d::VertexLayout::Position2D);
		hw3d::VertexBuffer bufFull{ lay };
		bufFull.EmplaceBack(dx::XMFLOAT2{ -1,1 });
		bufFull.EmplaceBack(dx::XMFLOAT2{ 1,1 });
		bufFull.EmplaceBack(dx::XMFLOAT2{ -1,-1 });
		bufFull.EmplaceBack(dx::XMFLOAT2{ 1,-1 });
		pVbFull = Bind::VertexBuffer::Resolve(gfx, "$Full", std::move(bufFull));
		std::vector<unsigned short> indices = { 0,1,2,1,3,2 };
		pIbFull = Bind::IndexBuffer::Resolve(gfx, "$Full", std::move(indices));

		// setup fullscreen shaders
		pVsFull = Bind::VertexShader::Resolve(gfx, "Fullscreen_VS.cso");
		pLayoutFull = Bind::InputLayout::Resolve(gfx, lay, pVsFull->GetBytecode());
		pSamplerFullPoint = Bind::Sampler::Resolve(gfx, false, true);
		pSamplerFullBilin = Bind::Sampler::Resolve(gfx, true, true);
		pBlenderMerge = Bind::Blender::Resolve(gfx, true);
	}
	void Accept(Job job, size_t target) noexcept
	{
		passes[target].Accept(job);
	}
	void Execute(Graphics& gfx) noexcept(!IS_DEBUG)
	{
		using namespace Bind;
		// normally this would be a loop with each pass defining it setup / etc.
		// and later on it would be a complex graph with parallel execution contingent
		// on input / output requirements

		// setup render target used for normal passes
		ds.Clear(gfx);
		rt1->Clear(gfx);
		gfx.BindSwapBuffer(ds);
		// main phong lighting pass
		Blender::Resolve(gfx, false)->Bind(gfx);
		Stencil::Resolve(gfx, Stencil::Mode::Off)->Bind(gfx);
		passes[0].Execute(gfx);
		// outline masking pass
		Stencil::Resolve(gfx, Stencil::Mode::Write)->Bind(gfx);
		NullPixelShader::Resolve(gfx)->Bind(gfx);
		passes[1].Execute(gfx);
		// outline drawing pass
		rt1->BindAsTarget(gfx);
		Stencil::Resolve(gfx, Stencil::Mode::Off)->Bind(gfx);
		passes[2].Execute(gfx);
		// fullscreen blur h-pass
		rt2->BindAsTarget(gfx);
		rt1->BindAsTexture(gfx, 0);
		pVbFull->Bind(gfx);
		pIbFull->Bind(gfx);
		pVsFull->Bind(gfx);
		pLayoutFull->Bind(gfx);
		pSamplerFullPoint->Bind(gfx);
		blur.Bind(gfx);
		blur.SetHorizontal(gfx);
		gfx.DrawIndexed(pIbFull->GetCount());
		// fullscreen blur v-pass + combine
		gfx.BindSwapBuffer(ds);
		rt2->BindAsTexture(gfx, 0u);
		pBlenderMerge->Bind(gfx);
		pSamplerFullBilin->Bind(gfx);
		Stencil::Resolve(gfx, Stencil::Mode::Mask)->Bind(gfx);
		blur.SetVertical(gfx);
		gfx.DrawIndexed(pIbFull->GetCount());
	}
	void Reset() noexcept
	{
		for (auto& p : passes)
		{
			p.Reset();
		}
	}
	void ShowWindows(Graphics& gfx)
	{
		if (ImGui::Begin("Blur"))
		{
			if (ImGui::SliderInt("Down Factor", &downFactor, 1, 16))
			{
				rt1.emplace(gfx, gfx.GetWidth() / downFactor, gfx.GetHeight() / downFactor);
				rt2.emplace(gfx, gfx.GetWidth() / downFactor, gfx.GetHeight() / downFactor);
			}
			blur.RenderWidgets(gfx);
		}
		ImGui::End();
	}
private:
	std::array<Pass, 3> passes;
	int downFactor = 1;
	DepthStencil ds;
	std::optional<RenderTarget> rt1;
	std::optional<RenderTarget> rt2;
	BlurPack blur;
	std::shared_ptr<Bind::VertexBuffer> pVbFull;
	std::shared_ptr<Bind::IndexBuffer> pIbFull;
	std::shared_ptr<Bind::VertexShader> pVsFull;
	std::shared_ptr<Bind::InputLayout> pLayoutFull;
	std::shared_ptr<Bind::Sampler> pSamplerFullPoint;
	std::shared_ptr<Bind::Sampler> pSamplerFullBilin;
	std::shared_ptr<Bind::Blender> pBlenderMerge;
};







// Remove the outline effect pass for some unresolved issue.
//class FrameCommander
//{
//public:
//	FrameCommander(Graphics& gfx)
//		:
//		ds(gfx, gfx.GetWidth(), gfx.GetHeight()),
//		rt(gfx, gfx.GetWidth(), gfx.GetHeight())
//	{
//		namespace dx = DirectX;
//
//		// setup fullscreen geometry
//		hw3d::VertexLayout lay;
//		lay.Append(hw3d::VertexLayout::Position2D);
//		hw3d::VertexBuffer bufFull{ lay };
//		bufFull.EmplaceBack(dx::XMFLOAT2{ -1,1 });
//		bufFull.EmplaceBack(dx::XMFLOAT2{ 1,1 });
//		bufFull.EmplaceBack(dx::XMFLOAT2{ -1,-1 });
//		bufFull.EmplaceBack(dx::XMFLOAT2{ 1,-1 });
//		pVbFull = Bind::VertexBuffer::Resolve(gfx, "$Full", std::move(bufFull));
//		std::vector<unsigned short> indices = { 0,1,2,1,3,2 };
//		pIbFull = Bind::IndexBuffer::Resolve(gfx, "$Full", std::move(indices));
//
//		// setup outline effect shaders
//		pPsFull = Bind::PixelShader::Resolve(gfx, "TEST_GaussBlurBruteForce_PS.cso");
//		pVsFull = Bind::VertexShader::Resolve(gfx, "TEST_Fullscreen_VS.cso");
//		pLayoutFull = Bind::InputLayout::Resolve(gfx, lay, pVsFull->GetBytecode());
//		pSamplerFull = Bind::Sampler::Resolve(gfx, false, true);
//		pBlenderFull = Bind::Blender::Resolve(gfx, true);
//	}
//
//
//	void Accept(Job job, size_t target) noexcept
//	{
//		passes[target].Accept(job);
//	}
//
//	void Execute(Graphics& gfx) const noexcept(!IS_DEBUG)
//	{
//		using namespace Bind;
//		// normally this would be a loop with each pass defining it setup / etc.
//		// and later on it would be a complex graph with parallel execution contingent
//		// on input / output requirements
//
//		// setup render target used for normal passes
//		ds.Clear(gfx);
//		rt.Clear(gfx);
//		gfx.BindSwapBuffer(ds);
//
//
//		// main phong lighting pass
//		Blender::Resolve(gfx, false)->Bind(gfx);
//		Stencil::Resolve(gfx, Stencil::Mode::Off)->Bind(gfx);
//		passes[0].Execute(gfx);
//		// outline masking pass
//		Stencil::Resolve(gfx, Stencil::Mode::Write)->Bind(gfx);
//		NullPixelShader::Resolve(gfx)->Bind(gfx);
//		passes[1].Execute(gfx);
//		// outline drawing pass
//		rt.BindAsTarget(gfx);  // bind the offscreen surface
//		Stencil::Resolve(gfx, Stencil::Mode::Off)->Bind(gfx);
//		passes[2].Execute(gfx);
//
//	}
//	void Reset() noexcept
//	{
//		for (auto& p : passes)
//		{
//			p.Reset();
//		}
//	}
//
//
//private:
//	DepthStencil ds;
//	std::array<Pass, 3> passes;
//	RenderTarget rt;
//	std::shared_ptr<Bind::VertexBuffer> pVbFull;
//	std::shared_ptr<Bind::IndexBuffer> pIbFull;
//	std::shared_ptr<Bind::VertexShader> pVsFull;
//	std::shared_ptr<Bind::PixelShader> pPsFull;
//	std::shared_ptr<Bind::InputLayout> pLayoutFull;
//	std::shared_ptr<Bind::Sampler> pSamplerFull;
//	std::shared_ptr<Bind::Blender> pBlenderFull;
//};