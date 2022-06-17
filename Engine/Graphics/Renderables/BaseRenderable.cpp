#include "BaseRenderable.h"
#include "Graphics/RenderManager.h"

using Matrix = DirectX::SimpleMath::Matrix;

void BaseRenderable::init(RenderManager& renderManager) {
	constantBuffer.init(renderManager.getDevice());
}

void BaseRenderable::transform(RenderManager& renderManager, DirectX::SimpleMath::Matrix& data) {
	constantBuffer.update(renderManager, &data);
}

void BaseRenderable::render(RenderManager& renderManager) {
	auto camera = renderManager.getCamera();

	auto wvp = transformation * Matrix::CreateTranslation(pos) * camera->viewMatrix * camera->projMatrix;

	transform(renderManager, wvp);

	transformation = Matrix::Identity;

	constantBuffer.push(renderManager);
}
