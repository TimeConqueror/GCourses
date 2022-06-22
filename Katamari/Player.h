#pragma once
#include "ITickable.h"
#include "Graphics/Renderables/ModelBasedRenderable.h"

class Player : public ModelBasedRenderable, ITickable
{
public:
	Player(Model* model, Texture* texture, const Material& material)
		: ModelBasedRenderable(model, texture, material) {
	}

	void move(DirectX::SimpleMath::Vector3 moveVec);
	void tick() override;
};

