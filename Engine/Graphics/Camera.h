#pragma once
#include <SimpleMath.h>

class Game;

class Camera {
	Game* game;
public:
	DirectX::SimpleMath::Matrix viewMatrix;
	DirectX::SimpleMath::Matrix projMatrix;

	Camera(Game* game);
	~Camera();

	DirectX::SimpleMath::Matrix getCameraMatrix() const;
	DirectX::SimpleMath::Vector3 getPos() const;
	DirectX::SimpleMath::Vector3 getForwardVector() const;
	DirectX::SimpleMath::Vector3 getUpVector() const;

	void update();
};

