#include "Player.h"
#include "Game.h"
#include "../Engine/Keyboard.h"

void Player::move(DirectX::SimpleMath::Vector3 moveVec) {
	this->pos += moveVec;
}

void Player::tick() {
	using namespace DirectX::SimpleMath;

	const InputController& inputController = Game::getInstance()->getInputController();
	const CameraHandler* cameraHandler = Game::getInstance()->getRenderManager().getCameraHandler();
	const float yaw = cameraHandler->yaw;
	const float pitch = cameraHandler->pitch;

	const bool forwardKeyDown = inputController.isKeyDown(Keyboard::KEY_W);
	const bool backKeyDown = inputController.isKeyDown(Keyboard::KEY_S);
	const bool leftKeyDown = inputController.isKeyDown(Keyboard::KEY_A);
	const bool rightKeyDown = inputController.isKeyDown(Keyboard::KEY_D);

	Vector3 velocity = Vector3::Zero;

	if (forwardKeyDown || backKeyDown || leftKeyDown || rightKeyDown) {
		float deltaYaw = 0;
		if (forwardKeyDown != backKeyDown) {
			deltaYaw = forwardKeyDown ? 0.0f : -180;
			if (leftKeyDown != rightKeyDown) {
				deltaYaw += (leftKeyDown ? -45.0f : 45.0f) * (forwardKeyDown ? 1 : -1);
			}
		}
		else if (leftKeyDown != rightKeyDown) {
			deltaYaw = leftKeyDown ? -90 : 90;
		}

		const float moveDir = -Math::PI/2 - (yaw - Math::toRadians(deltaYaw));
		velocity = Vector3(std::cos(moveDir), 0, std::sin(moveDir));
	}

	move(velocity);
}
