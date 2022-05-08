#pragma once
#include "Graphics.h"
#include <string>
#include <memory>
#include <filesystem>
#include "SimpleMathDX.h"

class Node;
class Mesh;
class ModelWindow;
struct aiMesh;
struct aiMaterial;
struct aiNode;
class RenderGraph;

namespace Rgph
{
	class RenderGraph;
}


class Model
{
public:
	Model(Graphics& gfx, const std::string& pathString, float scale = 1.0f);
	void Submit() const noexcept(!IS_DEBUG);
	//void ShowWindow(Graphics& gfx, const char* windowName = nullptr) noexcept;
	void SetRootTransform(DirectX::FXMMATRIX tf) noexcept;
	void Accept(class ModelProbe& probe);
	void LinkTechniques(Rgph::RenderGraph&);
	~Model() noexcept;
private:
	static std::unique_ptr<Mesh> ParseMesh(Graphics& gfx, const aiMesh& mesh, const aiMaterial* const* pMaterials, const std::filesystem::path& path, float scale);
	//std::unique_ptr<Node> ParseNode(int& nextId, const aiNode& node, DirectX::FXMMATRIX additionalTransform) noexcept;
	std::unique_ptr<Node> ParseNode(int& nextId, const aiNode& node, float scale) noexcept;
private:
	std::unique_ptr<Node> pRoot;
	std::vector<std::unique_ptr<Mesh>> meshPtrs;
};