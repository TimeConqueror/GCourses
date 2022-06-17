#pragma once

#include <SimpleMath.h>

#include "BaseRenderable.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../ConstantBuffer.h"
#include "IRenderable.h"
#include "../RenderType.h"
#include "../Shape.h"

class RenderManager;

class RenderableObject : public BaseRenderable {
	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;
	RenderType* renderType;

	bool shouldUpdate = false;
public:
	// in radians
	DirectX::SimpleMath::Quaternion rotation;
	DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One;

	RenderableObject(RenderType* renderType, Shape& shape);
	RenderableObject(RenderType* renderType, Shape&& shape);

	void init(RenderManager& renderManager) override;
	void render(RenderManager& renderManager) override;

	RenderType* getRenderType() const override;
};

