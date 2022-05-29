#include "RenderManager.h"
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
	constantBuffer.init(renderManager.getDevice());
}

void RenderableObject::transform(RenderManager& renderManager, Matrix& data) {
	constantBuffer.update(renderManager, &data);
}

void RenderableObject::prepare(RenderManager& renderManager) {
	auto camera = renderManager.getCamera();

	auto wvp = Matrix::CreateFromQuaternion(rotation) * Matrix::CreateScale(scale) * Matrix::CreateTranslation(pos) * camera->viewMatrix * camera->projMatrix;

	transform(renderManager, wvp);
}

RenderType* RenderableObject::getRenderType() {
	return renderType;
}
