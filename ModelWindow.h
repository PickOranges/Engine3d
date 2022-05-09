#pragma once
#include "Graphics.h"
#include "DynamicConstant.h"
#include <optional>
#include <unordered_map>

class Node;

class ModelWindow // pImpl idiom, only defined in this .cpp
{
public:
	void Show(Graphics& gfx, const char* windowName, const Node& root) noexcept;
	void ApplyParameters() noexcept(!IS_DEBUG);
private:
	DirectX::XMMATRIX GetTransform() const noexcept(!IS_DEBUG);
	const Dcb::Buffer& GetMaterial() const noexcept(!IS_DEBUG);
	bool TransformDirty() const noexcept(!IS_DEBUG);
	void ResetTransformDirty() noexcept(!IS_DEBUG);
	bool MaterialDirty() const noexcept(!IS_DEBUG);
	void ResetMaterialDirty() noexcept(!IS_DEBUG);
	bool IsDirty() const noexcept(!IS_DEBUG);
private:
	Node* pSelectedNode;
	struct TransformParameters
	{
		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};
	//struct NodeData
	//{
	//	TransformParameters tranformParams;
	//	bool transformParamsDirty;
	//	std::optional<Dcb::Buffer> materialCbuf;
	//	bool materialCbufDirty;
	//};
	//std::unordered_map<int, NodeData> transforms;
	std::unordered_map<int, TransformParameters> transforms;
};