#include "Player.h"
#include "Game.h"
#include "Katamari.h"
#include "../Engine/Keyboard.h"

void Player::move(DirectX::SimpleMath::Vector3 moveVec) {
	this->pos += moveVec;
}

void Player::tick() {
	Actor::tick();
	handleMovement();
	attemptCatchNearbies();
	updatePos(nullptr);
}

void Player::attemptCatchNearbies() {
	Katamari* game = static_cast<Katamari*>(Game::getInstance()->getInstance());
	for (Actor* entity : game->entities) {
		if(areColliding(*this, *entity)) {
			this->addChild(entity);
		}
	}
}

double Player::distanceBetween(const Actor& a, const Actor& b) {
	return std::sqrt(std::pow(a.pos.x - b.pos.x, 2) + std::pow(a.pos.y - b.pos.y, 2) + std::pow(a.pos.z - b.pos.z, 2));
}

bool Player::areColliding(const Actor& a, const Actor& b) {
	return distanceBetween(a, b) < (a.collisionRadius + b.collisionRadius);
}

void Player::handleMovement() {
	using namespace DirectX::SimpleMath;
	Game* game = Game::getInstance();

	const InputController& inputController = game->getInputController();
	const CameraHandler* cameraHandler = game->getRenderManager().getCameraHandler();
	const float yaw = cameraHandler->yaw;
	const float pitch = cameraHandler->pitch;

	const bool forwardKeyDown = inputController.isKeyDown(Keyboard::KEY_W);
	const bool backKeyDown = inputController.isKeyDown(Keyboard::KEY_S);
	const bool leftKeyDown = false;
	// const bool leftKeyDown = inputController.isKeyDown(Keyboard::KEY_A);
	// const bool rightKeyDown = inputController.isKeyDown(Keyboard::KEY_D);
	const bool rightKeyDown = false;

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

		const float moveDir = -Math::PI / 2 - (yaw - Math::toRadians(deltaYaw));
		velocity = Vector3(std::cos(moveDir), 0, std::sin(moveDir));


		//auto rollDir = moveDir + Math::PI / 2;
		//std::cout << rollDir << std::endl;
		//this->rollAxis = Vector3(std::cos(rollDir), 0, std::sin(rollDir));
		//this->rollQ = Quaternion::CreateFromAxisAngle(rollAxis,this->pitch);
	}

	move(velocity);

	Matrix cameraMatrix = Matrix::CreateFromYawPitchRoll(game->getRenderManager().getCameraHandler()->yaw, game->getRenderManager().getCameraHandler()->pitch, 0);
	Vector3 leftVec = cameraMatrix.Left();
	auto q = Quaternion::CreateFromAxisAngle(leftVec, this->pitch);
	//transformation *= Matrix::CreateFromQuaternion(q);

	rotation = Quaternion::CreateFromYawPitchRoll(game->getRenderManager().getCameraHandler()->yaw + Math::PI, 0, 0) * q;
	//rotation = q;
}

void Player::applyTransformation() {
	using namespace DirectX::SimpleMath;
	Game* game = Game::getInstance();
	const InputController& inputController = game->getInputController();
	transformation *= Matrix::CreateTranslation(Vector3(0, 0, -15));
	transformation *= Matrix::CreateRotationX(Math::toRadians(-90));
	//transformation *= Matrix::CreateFromYawPitchRoll(game->getRenderManager().getCameraHandler()->yaw + Math::PI, 0, 0);

	//transformation.

	//Quaternion fromYawPitchRoll = Quaternion::CreateFromAxisAngle(Vector3::Forward, 10);
	//fromYawPitchRoll.
	// std::cout << "Rot " << this->rollAxis.x << " " << this->rollAxis.y << " " << this->rollAxis.z << std::endl;

	if(inputController.isKeyDown(Keyboard::KEY_W)) {
		pitch += Math::toRadians(5);
	} else if(inputController.isKeyDown(Keyboard::KEY_S)) {
		pitch -= Math::toRadians(5);
	}
	
	// if (inputController.isKeyDown(Keyboard::KEY_A)) {
	// 	pitch -= Math::toRadians(5);
	// }
	// else if (inputController.isKeyDown(Keyboard::KEY_D)) {
	// 	pitch += Math::toRadians(5);
	// }

	//left-right only
	//const float moveDir = -Math::PI / 2 - game->getRenderManager().getCameraHandler()->yaw;
	///auto moveDirVec = Vector3(std::cos(moveDir), 0, std::sin(moveDir));
	//auto q1 = Quaternion::CreateFromAxisAngle(moveDirVec, yaw);
	//transformation *= Matrix::CreateFromQuaternion(q1);
	
	// Matrix cameraMatrix = Matrix::CreateFromYawPitchRoll(game->getRenderManager().getCameraHandler()->yaw, game->getRenderManager().getCameraHandler()->pitch, 0);
	// Vector3 leftVec = cameraMatrix.Left();
	// auto q = Quaternion::CreateFromAxisAngle(leftVec, pitch);
	//transformation *= Matrix::CreateFromQuaternion(q);

	//std::cout << rotation << std::endl;
	// if(rollAxis != Vector3::Zero) {
	// 	//auto q2 = Quaternion::CreateFromAxisAngle(rollAxis, pitch);
	// }

	Actor::applyTransformation();
}
