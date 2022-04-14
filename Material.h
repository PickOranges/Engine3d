#pragma once
#include "Graphics.h"
#include "BindableBase.h"
#include <vector>
#include <filesystem>
#include "Technique.h"


struct aiMaterial;
struct aiMesh;

class Material
{
public:
	Material(Graphics& gfx, const aiMaterial& material, const std::filesystem::path& path) noexcept(!IS_DEBUG);


	std::vector<Technique> GetTechniques() const noexcept;

	hw3d::VertexBuffer ExtractVertices(const aiMesh& mesh) const noexcept;

	std::vector<unsigned short> ExtractIndices(const aiMesh& mesh) const noexcept;
	std::shared_ptr<Bind::VertexBuffer> MakeVertexBindable(Graphics& gfx, const aiMesh& mesh, float scale = 1.0f) const noexcept(!IS_DEBUG);
	std::shared_ptr<Bind::IndexBuffer> MakeIndexBindable(Graphics& gfx, const aiMesh& mesh) const noexcept(!IS_DEBUG);

private:
	std::string MakeMeshTag(const aiMesh& mesh) const noexcept;
private:
	hw3d::VertexLayout vtxLayout;
	std::vector<Technique> techniques;
	std::string modelPath;
	std::string name;
};