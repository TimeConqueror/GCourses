#include "ModelBasedRenderable.h"

#include "BaseRenderable.h"
#include "Graphics/RenderManager.h"

void ModelBasedRenderable::init(RenderManager& renderManager) {
	BaseRenderable::init(renderManager);
	materialBuffer.init(renderManager.getDevice());
	materialBuffer.update(renderManager, &this->material);
}

RenderType* ModelBasedRenderable::getRenderType() const {
	return model->getRenderType();
}

void ModelBasedRenderable::render(RenderManager& renderManager) {
	BaseRenderable::render(renderManager);
	texture->pushAsShaderResource(renderManager, 0);
	materialBuffer.pushForPixelShader(renderManager, 1);
	model->render(renderManager);
}
