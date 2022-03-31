#include "TestCube.h"
#include "Cube.h"
#include "BindableBase.h"
#include "TransformCbuf.h"
#include "imgui/imgui.h"
#include "NullPixelShader.h"


TestCube::TestCube(Graphics& gfx, float size)
{
	using namespace Bind;
	namespace dx = DirectX;

	auto model = Cube::MakeIndependentTextured();
	model.Transform(dx::XMMatrixScaling(size, size, size));
	model.SetNormalsIndependentFlat();
	const auto geometryTag = "$cube." + std::to_string(size);
	//AddBind(VertexBuffer::Resolve(gfx, geometryTag, model.vertices));
	//AddBind(IndexBuffer::Resolve(gfx, geometryTag, model.indices));

	//AddBind(Texture::Resolve(gfx, "Images\\brickwall.jpg"));
	////AddBind(Texture::Resolve(gfx, "Images\\brickwall_normal.jpg", 1u));
	//AddBind(Sampler::Resolve(gfx));

	//auto pvs = VertexShader::Resolve(gfx, "PhongVS.cso");
	//auto pvsbc = pvs->GetBytecode();
	//AddBind(std::move(pvs));

	////AddBind(PixelShader::Resolve(gfx, "PhongPSNormalMap.cso"));
	//AddBind(PixelShader::Resolve(gfx, "PhongPS.cso"));

	//AddBind(PixelConstantBuffer<PSMaterialConstant>::Resolve(gfx, pmc, 1u));

	//AddBind(InputLayout::Resolve(gfx, model.vertices.GetLayout(), pvsbc));

	//AddBind(Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	////AddBind(std::make_shared<TransformCbufDual>(gfx, *this, 0u, 2u));
	//auto tcbdb = std::make_shared<TransformCbufDual>(gfx, *this, 0u, 2u);
	//AddBind(tcbdb);

	//AddBind(std::make_shared<Stencil>(gfx, Stencil::Mode::Write));


	//outlineEffect.push_back(VertexBuffer::Resolve(gfx, geometryTag, model.vertices));
	//outlineEffect.push_back(IndexBuffer::Resolve(gfx, geometryTag, model.indices));
	//pvs = VertexShader::Resolve(gfx, "SolidVS.cso");
	//pvsbc = pvs->GetBytecode();
	//outlineEffect.push_back(std::move(pvs));
	//outlineEffect.push_back(PixelShader::Resolve(gfx, "SolidPS.cso"));
	//struct SolidColorBuffer
	//{
	//	DirectX::XMFLOAT4 color = { 1.0f,0.4f,0.4f,1.0f };
	//} scb;
	//outlineEffect.push_back(PixelConstantBuffer<SolidColorBuffer>::Resolve(gfx, scb, 1u));
	//outlineEffect.push_back(InputLayout::Resolve(gfx, model.vertices.GetLayout(), pvsbc));
	//outlineEffect.push_back(Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	//outlineEffect.push_back(std::move(tcbdb));
	//outlineEffect.push_back(std::make_shared<Stencil>(gfx, Stencil::Mode::Mask));


	{
		// Tech 1: Normal Draw(Lambertian) 
		// 1 pass only
		Technique standard;
		{
			Step only(0);

			only.AddBindable(Texture::Resolve(gfx, "Images\\brickwall.jpg"));
			only.AddBindable(Sampler::Resolve(gfx));

			auto pvs = VertexShader::Resolve(gfx, "PhongVS.cso");
			auto pvsbc = pvs->GetBytecode();
			only.AddBindable(std::move(pvs));

			only.AddBindable(PixelShader::Resolve(gfx, "PhongPS.cso"));

			only.AddBindable(PixelConstantBuffer<PSMaterialConstant>::Resolve(gfx, pmc, 1u));

			only.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), pvsbc));

			only.AddBindable(std::make_shared<TransformCbuf>(gfx));

			standard.AddStep(std::move(only));
		}
		AddTechnique(std::move(standard));
	}

	{
		// Tech 2: Outline
		// 2 passes
		Technique outline;
		{
			// Pass 1: write/create mask stencil
			Step mask(1);

			auto pvs = VertexShader::Resolve(gfx, "SolidVS.cso");
			auto pvsbc = pvs->GetBytecode();
			mask.AddBindable(std::move(pvs));

			// TODO: better sub-layout generation tech for future consideration maybe
			mask.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), pvsbc));

			mask.AddBindable(std::make_shared<TransformCbuf>(gfx));

			// TODO: might need to specify rasterizer when doubled-sided models start being used

			outline.AddStep(std::move(mask));
		}


		{
			// Pass 2: scale up & use mask 
			Step draw(2);

			auto pvs = VertexShader::Resolve(gfx, "SolidVS.cso");
			auto pvsbc = pvs->GetBytecode();
			draw.AddBindable(std::move(pvs));

			// this can be pass-constant
			draw.AddBindable(PixelShader::Resolve(gfx, "SolidPS.cso"));

			// TODO: better sub-layout generation tech for future consideration maybe
			draw.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), pvsbc));

			// quick and dirty... nicer solution maybe takes a lamba... we'll see :)
			class TransformCbufScaling : public TransformCbuf
			{
			public:
				using TransformCbuf::TransformCbuf;
				void Bind(Graphics& gfx) noexcept override
				{
					const auto scale = dx::XMMatrixScaling(1.04f, 1.04f, 1.04f);
					auto xf = GetTransforms(gfx);
					xf.modelView = xf.modelView * scale;
					xf.modelViewProj = xf.modelViewProj * scale;
					UpdateBindImpl(gfx, xf);
				}
			};
			draw.AddBindable(std::make_shared<TransformCbufScaling>(gfx));

			// TODO: might need to specify rasterizer when doubled-sided models start being used

			outline.AddStep(std::move(draw));
		}
		AddTechnique(std::move(outline));
	}






}

void TestCube::SetPos(DirectX::XMFLOAT3 pos) noexcept
{
	this->pos = pos;
}

void TestCube::SetRotation(float roll, float pitch, float yaw) noexcept
{
	this->roll = roll;
	this->pitch = pitch;
	this->yaw = yaw;
}

DirectX::XMMATRIX TestCube::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(roll, pitch, yaw) *
		DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
}

void TestCube::SpawnControlWindow(Graphics& gfx, const char* name) noexcept
{
	if (ImGui::Begin(name))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &pos.x, -80.0f, 80.0f, "%.1f");
		ImGui::SliderFloat("Y", &pos.y, -80.0f, 80.0f, "%.1f");
		ImGui::SliderFloat("Z", &pos.z, -80.0f, 80.0f, "%.1f");
		ImGui::Text("Orientation");
		ImGui::SliderAngle("Roll", &roll, -180.0f, 180.0f);
		ImGui::SliderAngle("Pitch", &pitch, -180.0f, 180.0f);
		ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);
		//ImGui::Text("Shading");
		//bool changed0 = ImGui::SliderFloat("Spec. Int.", &pmc.specularIntensity, 0.0f, 1.0f);
		//bool changed1 = ImGui::SliderFloat("Spec. Power", &pmc.specularPower, 0.0f, 100.0f);
		//bool checkState = pmc.normalMappingEnabled == TRUE;
		//bool changed2 = ImGui::Checkbox("Enable Normal Map", &checkState);
		//pmc.normalMappingEnabled = checkState ? TRUE : FALSE;
		//if (changed0 || changed1 || changed2)
		//{
		//	QueryBindable<Bind::PixelConstantBuffer<PSMaterialConstant>>()->Update(gfx, pmc);
		//}
	}
	ImGui::End();
}