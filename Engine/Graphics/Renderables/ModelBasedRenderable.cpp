#include "ModelBasedRenderable.h"

#include "BaseRenderable.h"

void ModelBasedRenderable::init(RenderManager& renderManager) {
	BaseRenderable::init(renderManager);
}

RenderType* ModelBasedRenderable::getRenderType() const {
	return model->getRenderType();
}

void ModelBasedRenderable::render(RenderManager& renderManager) {
	BaseRenderable::render(renderManager);
	texture->pushAsShaderResource(renderManager, 0);
	model->render(renderManager);
}
