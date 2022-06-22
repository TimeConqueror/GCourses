#include "CameraHandler.h"
#include "Game.h"
#include "../Keyboard.h"
#include "../MathHelper.h"
#include "Renderables/BaseRenderable.h"

CameraHandler::CameraHandler(Game* game, Camera* camera): game(game), camera(camera) {
	
}

void CameraHandler::update(const BaseRenderable* trackingObject, float partialTick) {
	auto inputHandler = game->getInputController();

	const auto rotationMatrix = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(yaw, pitch, 0);
	cameraPos = trackingObject->pos - rotationMatrix.Forward() * 100;

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
