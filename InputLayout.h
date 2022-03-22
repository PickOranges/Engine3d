#pragma once
#include "Bindable.h"
#include "Vertex.h"


namespace Bind {
	class InputLayout : public Bindable
	{
	public:
		InputLayout(Graphics& gfx, hw3d::VertexLayout layout, ID3DBlob* pVertexShaderBytecode);
		void Bind(Graphics& gfx) noexcept override;
		static std::shared_ptr<Bindable> Resolve(Graphics& gfx, const hw3d::VertexLayout& layout, ID3DBlob* pVertexShaderBytecode);
		static std::string GenerateUID(const hw3d::VertexLayout& layout, ID3DBlob* pVertexShaderBytecode = nullptr);
		std::string GetUID() const noexcept override;
	protected:
		hw3d::VertexLayout layout;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	};
}


