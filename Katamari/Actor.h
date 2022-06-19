#pragma once
#include "MathHelper.h"
#include "Graphics/Renderables/ModelBasedRenderable.h"

class Actor: public ModelBasedRenderable
{
public:
	Actor(Model* model, Texture* texture, const Material& material)
		: ModelBasedRenderable(model, texture, material) {
	}

protected:
	void applyTransformation() override;
};

inline void Actor::applyTransformation() {
	BaseRenderable::applyTransformation();

	const long millis = Math::currentMillis();

	const double turnProgress = millis % 10000 / static_cast<double>(10000);
	const double turnAngle = Math::PI * 2 * turnProgress;

	transformation *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle({ 1.0F, 0.5F, 0.5F }, turnAngle));
}

