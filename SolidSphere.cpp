#include "SolidSphere.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "Sphere.h"
#include "Vertex.h"
#include "BindableCodex.h"


SolidSphere::SolidSphere(Graphics& gfx, float radius)
{
	namespace dx = DirectX;
	using namespace Bind;

	auto model = Sphere::Make();
	const auto geometryTag = "$sphere." + std::to_string(radius);
	AddBind(VertexBuffer::Resolve(gfx, geometryTag, model.vertices));
	AddBind(IndexBuffer::Resolve(gfx, geometryTag, model.indices));

	auto pvs = VertexShader::Resolve(gfx, "SolidVS.cso");
	auto pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));

	AddBind(PixelShader::Resolve(gfx, "SolidPS.cso"));
	struct PSColorConstant
	{
		dx::XMFLOAT3 color = { 1.0f,1.0f,1.0f };
		float padding;
	}colorConst;

	AddBind(PixelConstantBuffer<PSColorConstant>::Resolve(gfx, colorConst,1u));

	AddBind(InputLayout::Resolve(gfx, model.vertices.GetLayout(), pvsbc));

	AddBind(Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_shared<TransformCbuf>(gfx, *this));

	AddBind(Blender::Resolve(gfx, false));

	AddBind(Rasterizer::Resolve(gfx, false));

	AddBind(std::make_shared<Stencil>(gfx, Stencil::Mode::Off));
}

void SolidSphere::SetPos(DirectX::XMFLOAT3 pos) noexcept
{
	this->pos = pos;
}

DirectX::XMMATRIX SolidSphere::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
}