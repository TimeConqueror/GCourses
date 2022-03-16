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
	float x = 0;
	float y = 0;
	bool shouldUpdate = false;
public:
	RenderableObject(std::vector<Vertex> vertices, const std::vector<uint>& indexes);

	void init(RenderManager& renderManager);
	void transform(RenderManager& renderManager, ConstantBufferData&& data);
	void setX(float x);
	void setY(float y);
	float getX() const;
	float getY() const;
private:
	void prepare(RenderManager& renderManager);
};

