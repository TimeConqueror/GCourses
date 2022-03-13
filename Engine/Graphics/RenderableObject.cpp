#include "RenderManager.h"
#include "RenderableObject.h"

RenderableObject::RenderableObject(std::vector<Vertex> vertices, const std::vector<uint>& indices):
vertexBuffer(vertices), indexBuffer(indices)
{
}

void RenderableObject::init(RenderManager& renderManager) {
	vertexBuffer.init(renderManager.getDevice());
	indexBuffer.init(renderManager.getDevice());
	constantBuffer.init(renderManager.getDevice());
}

void RenderableObject::transform(RenderManager& renderManager, ConstantBufferData* data) {
	constantBuffer.update(renderManager, data);
}
