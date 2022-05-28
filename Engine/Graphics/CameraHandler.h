#pragma once
#include <SimpleMath.h>
#include "Camera.h"
#include "MathHelper.h"

class Game;

class CameraHandler {
public:
	float yaw = 0; // horizontal rotation, in radians
	float pitch = 0; // up and down, in radians

	float velocityMagnitude = 1.0F;
	float mouseSensivity = 1.0F;

	Game* game;
	Camera* camera;

	DirectX::SimpleMath::Vector3 cameraPos;

	CameraHandler(Game* game, Camera* camera);
	void update(float partialTick);
private:
	void handleMouseMove();
};

