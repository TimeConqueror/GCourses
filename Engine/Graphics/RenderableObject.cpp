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

void RenderableObject::transform(RenderManager& renderManager, ConstantBufferData&& data) {
	constantBuffer.update(renderManager, &data);
}


void RenderableObject::setX(float x) {
	this->x = x;
	shouldUpdate = true;
}

void RenderableObject::setY(float y) {
	this->y = y;
	shouldUpdate = true;
}

float RenderableObject::getX() const {
	return x;
}

float RenderableObject::getY() const {
	return y;
}

void RenderableObject::prepare(RenderManager& renderManager) {
	if (shouldUpdate) {
		transform(renderManager, ConstantBufferData(x, y));
		shouldUpdate = false;
	}
}
