#include "../RenderManager.h"
#include "RenderableObject.h"

using Matrix = DirectX::SimpleMath::Matrix;

RenderableObject::RenderableObject(RenderType* renderType, Shape& shape) :
	vertexBuffer(shape.getVertices()), indexBuffer(shape.getIndexes()), renderType(renderType) {
}

RenderableObject::RenderableObject(RenderType* renderType, Shape&& shape) :
	vertexBuffer(shape.getVertices()), indexBuffer(shape.getIndexes()), renderType(renderType) {
}

void RenderableObject::init(RenderManager& renderManager) {
	vertexBuffer.init(renderManager.getDevice());
	indexBuffer.init(renderManager.getDevice());
	BaseRenderable::init(renderManager);
}

void RenderableObject::render(RenderManager& renderManager) {
	transformation = transformation * Matrix::CreateFromQuaternion(rotation) * Matrix::CreateScale(scale);
	BaseRenderable::render(renderManager);

	vertexBuffer.push(renderManager);
	indexBuffer.push(renderManager);

	renderManager.getContext()->DrawIndexed(indexBuffer.getSize(), 0, 0);
}

RenderType* RenderableObject::getRenderType() const {
	return renderType;
}
