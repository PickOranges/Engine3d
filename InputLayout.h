#pragma once
#include "Bindable.h"
#include "Vertex.h"


namespace Bind {
	class VertexShader;

	class InputLayout : public Bindable
	{
	public:
		InputLayout(Graphics& gfx, hw3d::VertexLayout layout, const VertexShader& vs);
		void Bind(Graphics& gfx) noexcept(!IS_DEBUG) override;
		const hw3d::VertexLayout GetLayout() const noexcept;
		static std::shared_ptr<InputLayout> Resolve(Graphics& gfx, const hw3d::VertexLayout& layout, const VertexShader& vs);
		static std::string GenerateUID(const hw3d::VertexLayout& layout, const VertexShader& vs);
		std::string GetUID() const noexcept override;
	protected:
		std::string vertexShaderUID;
		hw3d::VertexLayout layout;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	};
}


