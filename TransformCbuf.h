#pragma once
#include "ConstantBuffers.h"
#include "Drawable.h"
#include <DirectXMath.h>

namespace Bind {
	class TransformCbuf : public CloningBindable
	{
	protected:
		struct Transforms
		{
			DirectX::XMMATRIX modelView;
			DirectX::XMMATRIX modelViewProj;
		};
	public:
		//TransformCbuf(Graphics& gfx, const Drawable& parent, UINT slot = 0u);
		TransformCbuf(Graphics& gfx, UINT slot = 0u);
		void Bind(Graphics& gfx) noexcept override;
		void InitializeParentReference(const Drawable& parent) noexcept override;
		std::unique_ptr<CloningBindable> Clone() const noexcept override;
	protected:
		void UpdateBindImpl(Graphics& gfx, const Transforms& tf) noexcept;
		Transforms GetTransforms(Graphics& gfx) noexcept;

	private:
		static std::unique_ptr<VertexConstantBuffer<Transforms>> pVcbuf;
		const Drawable* pParent = nullptr;
	};



//	// This class is for binding TF on both VertexShader and PixelShader
//	class TransformCbufDual : public TransformCbuf
//	{
//	public:
//		TransformCbufDual(Graphics& gfx, const Drawable& parent, UINT slotV = 0u, UINT slotP = 0u);
//		void Bind(Graphics& gfx) noexcept override;
//	protected:
//		void UpdateBindImpl(Graphics& gfx, const Transforms& tf) noexcept;
//	private:
//		static std::unique_ptr<PixelConstantBuffer<Transforms>> pPcbuf;
//	};



}
