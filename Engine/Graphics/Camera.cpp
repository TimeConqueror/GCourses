#include "Camera.h"
#include "Game.h"
#include "../MathHelper.h"

Camera::Camera(Game* game): game(game) {
	viewMatrix = DirectX::SimpleMath::Matrix::Identity;
	update();
}

Camera::~Camera() {
}

//TODO OPTIMIZE START
DirectX::SimpleMath::Matrix Camera::getCameraMatrix() const {
	return viewMatrix * projMatrix;
}

DirectX::SimpleMath::Vector3 Camera::getPos() const {
	DirectX::SimpleMath::Matrix inverted;
	viewMatrix.Invert(inverted);

	return inverted.Translation();
}

DirectX::SimpleMath::Vector3 Camera::getForwardVector() const {
	DirectX::SimpleMath::Matrix inverted;
	viewMatrix.Invert(inverted);

	return inverted.Forward();
}

DirectX::SimpleMath::Vector3 Camera::getUpVector() const {
	DirectX::SimpleMath::Matrix inverted;
	viewMatrix.Invert(inverted);

	return inverted.Up();
}

//TODO OPTIMIZE END

void Camera::update() {
	projMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		Math::PI * 0.35f,
		(float) game->getWindow().getWidth() / (float) game->getWindow().getHeight(),
		0.1F,
		10000.0F
	);
}
