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
		TransformCbuf(Graphics& gfx, UINT slot = 0u);
		void Bind(Graphics& gfx) noexcept(!IS_DEBUG) override;
		void InitializeParentReference(const Drawable& parent) noexcept override;
		std::unique_ptr<CloningBindable> Clone() const noexcept override;
	protected:
		void UpdateBindImpl(Graphics& gfx, const Transforms& tf) noexcept(!IS_DEBUG);
		Transforms GetTransforms(Graphics& gfx) noexcept(!IS_DEBUG);
	private:
		static std::unique_ptr<VertexConstantBuffer<Transforms>> pVcbuf;
		const Drawable* pParent = nullptr;
	};
}
