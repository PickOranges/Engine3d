#pragma once
#include "Graphics.h"
#include "Drawable.h"
#include "SimpleMathDX.h"



class Material;
struct aiMesh;


class Mesh : public Drawable
{
public:
	Mesh(Graphics& gfx, const Material& mat, const aiMesh& mesh, float scale = 1.0f) noexcept(!IS_DEBUG);
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void Submit(DirectX::FXMMATRIX accumulatedTranform) const noexcept(!IS_DEBUG);
private:
	mutable DirectX::XMFLOAT4X4 transform;
};