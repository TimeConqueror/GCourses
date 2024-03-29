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

	Matrix lightViewProj = Matrix::Identity;

	Transform transformData{
		transformation,
		transformation * camera->viewMatrix * camera->projMatrix,
		transformation.Transpose().Invert(),
		transformation * lightViewProj
	};

	transform(renderManager, transformData);

	constantBuffer.pushForVertexShader(renderManager);

	transformation = Matrix::Identity;

}

void BaseRenderable::applyTransformation() {
	transformation *= Matrix::CreateScale(scale, scale, scale);
	transformation *= Matrix::CreateFromQuaternion(rotation);
	transformation *= Matrix::CreateTranslation(pos);
}
