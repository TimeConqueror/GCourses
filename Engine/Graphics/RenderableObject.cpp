#include "RenderManager.h"
#include "RenderableObject.h"

RenderableObject::RenderableObject(Shape& shape):
vertexBuffer(shape.getVertices()), indexBuffer(shape.getIndexes())
{}

RenderableObject::RenderableObject(Shape&& shape) :
	vertexBuffer(shape.getVertices()), indexBuffer(shape.getIndexes()) {
}

void RenderableObject::init(RenderManager& renderManager) {
	vertexBuffer.init(renderManager.getDevice());
	indexBuffer.init(renderManager.getDevice());
	constantBuffer.init(renderManager.getDevice());
}

void RenderableObject::transform(RenderManager& renderManager, DirectX::SimpleMath::Matrix& data) {
	constantBuffer.update(renderManager, &data);
}

void RenderableObject::setPos(const DirectX::SimpleMath::Vector3& vec) {
	this->pos.x = vec.x;
	this->pos.y = vec.y;
	this->pos.z = vec.z;
}

void RenderableObject::setPos(const float x, const float y, const float z) {
	this->pos.x = x;
	this->pos.y = y;
	this->pos.z = z;
}

DirectX::SimpleMath::Vector3& RenderableObject::getPos() {
	return pos;
}

void RenderableObject::prepare(RenderManager& renderManager) {
	auto camera = renderManager.getCamera();
	std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
	auto wvp = DirectX::SimpleMath::Matrix::CreateTranslation(pos) * camera->viewMatrix * camera->projMatrix;

	transform(renderManager, wvp);
}
