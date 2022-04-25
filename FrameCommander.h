#pragma once
#include <array>
#include "BindableBase.h"
#include "Graphics.h"
#include "Job.h"
#include "Pass.h"
#include "DepthStencil.h"
#include "RenderTarget.h"
#include <array>

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
//
//
//		// new: output the normal scenen and input from blurred outline.
//		// ie. box outline is blurred, but the sponza scene is not blurred!
//		gfx.BindSwapBuffer(ds);				  // bind the output, this is where the fullscreen effect will finally go to.	
//		rt.BindAsTexture(gfx, 0);			  // bind the input, this is what we use for blur the outline.		
//		pVbFull->Bind(gfx);
//		pIbFull->Bind(gfx);
//		pVsFull->Bind(gfx);
//		//pPsFull->Bind(gfx);
//		pLayoutFull->Bind(gfx);
//		pSamplerFull->Bind(gfx);
//		pBlenderFull->Bind(gfx);
//		Stencil::Resolve(gfx, Stencil::Mode::Mask)->Bind(gfx);
//		gfx.DrawIndexed(pIbFull->GetCount());
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







// Remove the outline effect pass for some unresolved issue.
class FrameCommander
{
public:
	FrameCommander(Graphics& gfx)
		:
		ds(gfx, gfx.GetWidth(), gfx.GetHeight()),
		rt(gfx, gfx.GetWidth(), gfx.GetHeight())
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

		// setup outline effect shaders
		pPsFull = Bind::PixelShader::Resolve(gfx, "TEST_GaussBlurBruteForce_PS.cso");
		pVsFull = Bind::VertexShader::Resolve(gfx, "TEST_Fullscreen_VS.cso");
		pLayoutFull = Bind::InputLayout::Resolve(gfx, lay, pVsFull->GetBytecode());
		pSamplerFull = Bind::Sampler::Resolve(gfx, false, true);
		pBlenderFull = Bind::Blender::Resolve(gfx, true);
	}


	void Accept(Job job, size_t target) noexcept
	{
		passes[target].Accept(job);
	}

	void Execute(Graphics& gfx) const noexcept(!IS_DEBUG)
	{
		using namespace Bind;
		// normally this would be a loop with each pass defining it setup / etc.
		// and later on it would be a complex graph with parallel execution contingent
		// on input / output requirements

		// setup render target used for normal passes
		ds.Clear(gfx);
		rt.Clear(gfx);
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
		rt.BindAsTarget(gfx);  // bind the offscreen surface
		Stencil::Resolve(gfx, Stencil::Mode::Off)->Bind(gfx);
		passes[2].Execute(gfx);

	}
	void Reset() noexcept
	{
		for (auto& p : passes)
		{
			p.Reset();
		}
	}


private:
	DepthStencil ds;
	std::array<Pass, 3> passes;
	RenderTarget rt;
	std::shared_ptr<Bind::VertexBuffer> pVbFull;
	std::shared_ptr<Bind::IndexBuffer> pIbFull;
	std::shared_ptr<Bind::VertexShader> pVsFull;
	std::shared_ptr<Bind::PixelShader> pPsFull;
	std::shared_ptr<Bind::InputLayout> pLayoutFull;
	std::shared_ptr<Bind::Sampler> pSamplerFull;
	std::shared_ptr<Bind::Blender> pBlenderFull;
};