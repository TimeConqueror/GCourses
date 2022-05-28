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

	DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero;
	bool shouldUpdate = false;
public:
	RenderableObject(RenderType* renderType, Shape& shape);
	RenderableObject(RenderType* renderType, Shape&& shape);

	void init(RenderManager& renderManager);
	void transform(RenderManager& renderManager, DirectX::SimpleMath::Matrix& data);
	void setPos(const DirectX::SimpleMath::Vector3& vec);
	void setPos(float x, float y, float z);

	DirectX::SimpleMath::Vector3& getPos();
	RenderType* getRenderType();
private:
	void prepare(RenderManager& renderManager);
};

