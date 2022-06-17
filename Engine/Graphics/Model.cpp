#include "Model.h"

#include "RenderManager.h"

void Model::init(RenderManager& renderManager) {
	for (VertexBuffer<PTVertex>& vertexBuffer : vertexBuffers) {
		vertexBuffer.init(renderManager.getDevice());
	}
	for (IndexBuffer& indexBuffer : indexBuffers) {
		indexBuffer.init(renderManager.getDevice());
	}
}

void Model::render(RenderManager& renderManager) {
	for (int i = 0; i < vertexBuffers.size(); ++i) {
		vertexBuffers[i].push(renderManager);
		indexBuffers[i].push(renderManager);
		renderManager.getContext()->DrawIndexed(indexBuffers[i].getSize(), 0, 0);
	}
}

RenderType* Model::getRenderType() const {
	return renderType;
}
