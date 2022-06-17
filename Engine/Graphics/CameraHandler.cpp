#include "CameraHandler.h"
#include "Game.h"
#include "../Keyboard.h"
#include "../MathHelper.h"

CameraHandler::CameraHandler(Game* game, Camera* camera): game(game), camera(camera) {
	
}

void CameraHandler::update(float partialTick) {
	auto inputHandler = game->getInputController();

	auto rotationMatrix = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(yaw, pitch, 0);

	auto velocity = DirectX::SimpleMath::Vector3::Zero;
	if (inputHandler.isKeyDown(KEY_W)) {
		velocity += DirectX::SimpleMath::Vector3(1.0F, 0.0F, 0.0F);
	}
	if (inputHandler.isKeyDown(KEY_S)) velocity += DirectX::SimpleMath::Vector3(-1.0F, 0.0F, 0.0F);
	if (inputHandler.isKeyDown(KEY_A)) velocity += DirectX::SimpleMath::Vector3(0.0F, 0.0F, -1.0F);
	if (inputHandler.isKeyDown(KEY_D)) velocity += DirectX::SimpleMath::Vector3(0.0F, 0.0F, 1.0F);

	if (inputHandler.isKeyDown(KEY_SPACE)) velocity += DirectX::SimpleMath::Vector3(0.0F, 1.0F, 0.0F);
	if (inputHandler.isKeyDown(KEY_SHIFT)) velocity += DirectX::SimpleMath::Vector3(0.0F, -1.0F, 0.0F);


	if (inputHandler.isKeyDown(KEY_PLUS)) velocityMagnitude += 1;
	if (inputHandler.isKeyDown(KEY_MINUS)) velocityMagnitude = std::max<float>(velocityMagnitude - 1, 1);

	velocity.Normalize();

	auto velDir = rotationMatrix.Forward() * velocity.x + DirectX::SimpleMath::Vector3::Up * velocity.y + rotationMatrix.Right() * velocity.z;

	if (velDir.Length() != 0) {
		velDir.Normalize();
	}

	cameraPos = cameraPos + velDir * velocityMagnitude * partialTick;
	camera->viewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(cameraPos, cameraPos + rotationMatrix.Forward(), rotationMatrix.Up());
	camera->update();

	handleMouseMove();
}

void CameraHandler::handleMouseMove() {
	auto inputController = game->getInputController();
	if(inputController.isKeyDown(KEY_Z)) {
		return;
	}

	yaw -= inputController.getMouseDx() * 0.003F * mouseSensivity;
	//yaw = Math::wrapRadians(yaw);
	pitch -= inputController.getMouseDy() * 0.003F * mouseSensivity;
	//pitch = Math::wrapRadians(pitch);
}
