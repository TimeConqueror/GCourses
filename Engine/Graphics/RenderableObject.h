#pragma once

#include <SimpleMath.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "RenderType.h"
#include "Shape.h"

class RenderManager;

class RenderableObject {
	friend void RenderType::render(RenderManager& renderManager, RenderableObject& object);

	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;
	ConstantBuffer<DirectX::SimpleMath::Matrix> constantBuffer;
	RenderType* renderType;

	bool shouldUpdate = false;
public:
	DirectX::SimpleMath::Vector3 pos;
	// in radians
	DirectX::SimpleMath::Quaternion rotation;
	DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One;

	RenderableObject(RenderType* renderType, Shape& shape);
	RenderableObject(RenderType* renderType, Shape&& shape);

	void init(RenderManager& renderManager);

	RenderType* getRenderType();
private:
	void transform(RenderManager& renderManager, DirectX::SimpleMath::Matrix& data);
	void prepare(RenderManager& renderManager);
};

