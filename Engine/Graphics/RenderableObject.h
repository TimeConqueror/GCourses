#pragma once

#include <SimpleMath.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"
#include "RenderType.h"
#include "Shape.h"

class RenderManager;

class RenderableObject {
	friend void RenderType::render(RenderManager& renderManager, RenderableObject& object);

	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	ConstantBuffer<DirectX::SimpleMath::Matrix> constantBuffer;

	DirectX::SimpleMath::Vector3 pos;
	bool shouldUpdate = false;
public:
	RenderableObject(Shape& shape);
	RenderableObject(Shape&& shape);

	void init(RenderManager& renderManager);
	void transform(RenderManager& renderManager, DirectX::SimpleMath::Matrix& data);
	void setPos(const DirectX::SimpleMath::Vector3& vec);
	void setPos(float x, float y, float z);

	DirectX::SimpleMath::Vector3& getPos();
private:
	void prepare(RenderManager& renderManager);
};

