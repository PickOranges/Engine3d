#pragma once
#include <assimp/scene.h>
#include "BindableBase.h"
#include <vector>
#include <filesystem>
#include "Technique.h"

class Material
{
public:
	Material(Graphics& gfx, const aiMaterial* pMaterial, const std::filesystem::path& path) noexcept(!IS_DEBUG)
	{

	}
	hw3d::VertexBuffer ExtractVertices(const aiMesh& mesh) const noexcept
	{
		using Type = hw3d::VertexLayout::ElementType;
		hw3d::VertexBuffer buf{ vtxLayout };
		buf.Resize(mesh.mNumVertices);
		if (vtxLayout.Has<Type::Position3D>())
		{
			for (int i = 0; i < mesh.mNumVertices; i++)
			{
				buf[i].
			}
		}
	}
	std::vector<Technique> GetTechniques() const noexcept
	{
		return techniques;
	}
private:
	hw3d::VertexLayout vtxLayout;
	std::vector<Technique> techniques;
};