#include "BaseRenderable.h"
#include "Graphics/RenderManager.h"

using Matrix = DirectX::SimpleMath::Matrix;

void BaseRenderable::init(RenderManager& renderManager) {
	constantBuffer.init(renderManager.getDevice());
}

void BaseRenderable::transform(RenderManager& renderManager, Transform& data) {
	constantBuffer.update(renderManager, &data);
}

void BaseRenderable::render(RenderManager& renderManager) {
	auto camera = renderManager.getCamera();

	applyTransformation();

	Transform transformData{
		transformation,
		transformation * camera->viewMatrix * camera->projMatrix,
		transformation.Transpose().Invert()
	};

	transform(renderManager, transformData);

	transformation = Matrix::Identity;

	constantBuffer.pushForVertexShader(renderManager);
}

void BaseRenderable::applyTransformation() {
	transformation *= Matrix::CreateTranslation(pos);
}
