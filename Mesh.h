#pragma once
#include "Drawable.h"
#include "BindableBase.h"
#include "ConstantBuffers.h"
#include "Vertex.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "imgui/imgui.h"
#include <type_traits>
#include <optional>
#include <filesystem>
#include "DynamicConstant.h"
#include <string>
#include "FrameCommander.h"



class Material;

class ModelException : public ExceptionBase
{
public:
	ModelException(int line, const char* file, std::string note) noexcept;
	const char* what() const noexcept override;
	const char* GetType() const noexcept override;
	const std::string& GetNote() const noexcept;
private:
	std::string note;
};



class Mesh : public Drawable
{
public:
	Mesh(Graphics& gfx, const Material& mat, const aiMesh& mesh) noexcept(!IS_DEBUG);
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void Submit(FrameCommander& frame, DirectX::FXMMATRIX accumulatedTranform) const noexcept(!IS_DEBUG);
private:
	mutable DirectX::XMFLOAT4X4 transform;
};



class Node
{
	friend class Model;

public:
	Node(int id, const std::string& name, std::vector<Mesh*> meshPtrs, const DirectX::XMMATRIX& transform) noexcept(!IS_DEBUG);
	void Submit(FrameCommander& frame,DirectX::FXMMATRIX accumulatedTransform) const noexcept(!IS_DEBUG);
	void SetAppliedTransform(DirectX::FXMMATRIX transform) noexcept;
	const DirectX::XMFLOAT4X4& GetAppliedTransform() const noexcept;
	int GetId() const noexcept;
	void ShowTree(Node*& pSelectedNode) const noexcept;
private:
	void AddChild(std::unique_ptr<Node> pChild) noexcept(!IS_DEBUG);
private:
	std::string name;
	int id;
	std::vector<std::unique_ptr<Node>> childPtrs;
	std::vector<Mesh*> meshPtrs;
	DirectX::XMFLOAT4X4 transform;
	DirectX::XMFLOAT4X4 appliedTransform;
};



class Model
{
public:
	Model(Graphics& gfx, const std::string& pathString, float scale = 1.0f);
	void Submit(FrameCommander& frame) const noexcept(!IS_DEBUG);
	void ShowWindow(Graphics& gfx, const char* windowName = nullptr) noexcept;
	void SetRootTransform(DirectX::FXMMATRIX tf) noexcept;
	~Model() noexcept;
private:
	static std::unique_ptr<Mesh> ParseMesh(Graphics& gfx, const aiMesh& mesh, const aiMaterial* const* pMaterials, const std::filesystem::path& path, float scale);
	std::unique_ptr<Node> ParseNode(int& nextId, const aiNode& node) noexcept;
private:
	std::unique_ptr<Node> pRoot;
	std::vector<std::unique_ptr<Mesh>> meshPtrs;
	std::unique_ptr<class ModelWindow> pWindow;  // Forward declarition of class ModelWindow for pImpl.
};

