#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"
#include "RenderType.h"

class RenderManager;

class RenderableObject {
	friend void RenderType::render(RenderManager& renderManager, RenderableObject& object);

	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	ConstantBuffer constantBuffer;

public:
	RenderableObject(std::vector<Vertex> vertices, const std::vector<uint>& indexes);

	void init(RenderManager& renderManager);
	void transform(RenderManager& renderManager, ConstantBufferData* data);
};

