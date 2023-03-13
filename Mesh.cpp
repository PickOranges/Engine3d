#include "Mesh.h"
#include "imgui/imgui.h"
#include "Surface.h"
#include <unordered_map>
#include <sstream>
#include <filesystem>
#include "DynamicConstant.h"
#include "ConstantBuffersEx.h"
#include "LayoutCodex.h"
#include "Stencil.h"


namespace dx = DirectX;


// Mesh
Mesh::Mesh(Graphics& gfx, const Material& mat, const aiMesh& mesh, float scale) noexcept(!IS_DEBUG)
	:
	Drawable(gfx, mat, mesh, scale)
{}

DirectX::XMMATRIX Mesh::GetTransformXM() const noexcept
{
	return DirectX::XMLoadFloat4x4(&transform);
}


void Mesh::Submit(dx::FXMMATRIX accumulatedTranform) const noexcept(!IS_DEBUG)
{
	dx::XMStoreFloat4x4(&transform, accumulatedTranform);
	Drawable::Submit();
}
