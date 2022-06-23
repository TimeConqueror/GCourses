#pragma once
#include "Actor.h"
#include "ITickable.h"
#include "Graphics/Renderables/ModelBasedRenderable.h"

class Player : public Actor, ITickable
{
public:
	Player(Model* model, Texture* texture, const Material& material)
		: Actor(model, texture, material) {
	}

	float pitch;
	float yaw;

	float rotSpeed = 5.0F;

	// DirectX::SimpleMath::Vector3 rollAxis = DirectX::SimpleMath::Vector3::Zero;
	// DirectX::SimpleMath::Quaternion rollQ;

	void move(DirectX::SimpleMath::Vector3 moveVec);
	void tick() override;
	void attemptCatchNearbies();
	void handleMovement();

protected:
	void applyTransformation() override;
private:
	double distanceBetween(const Actor& a, const Actor& b);
	bool areColliding(const Actor& a, const Actor& b);
	bool canStitch(const Actor* target) const;
	void grow(const Actor* stitchedActor);
};

