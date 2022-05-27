#include "SolarDemo.h"
#include "../Engine/Keyboard.h"

void SolarDemo::init() {
	RenderManager& renderManager = getRenderManager();
	std::cout << "Initializing..." << std::endl;
}

void SolarDemo::tick() {
	handleInput();
}

void SolarDemo::handleWinState() {
}

void SolarDemo::handleInput() {

	// InputController& inputController = getInputController();
	//
	// if (inputController.isKeyDown(Keyboard::KEY_SPACE)) {
	// 	paused = !paused;
	// }
	//
	// if (paused) return;
	//
	// float speed = 0.05F;
	// if(inputController.isKeyDown(Keyboard::KEY_W)) {
	// 	leftBoard.move(speed, getPartialTick());
	// } else if (inputController.isKeyDown(Keyboard::KEY_S)) {
	// 	leftBoard.move(-speed, getPartialTick());
	// } else if (inputController.isKeyDown(Keyboard::KEY_ARROW_UP)) {
	// 	rightBoard.move(speed, getPartialTick());
	// } else if (inputController.isKeyDown(Keyboard::KEY_ARROW_DOWN)) {
	// 	rightBoard.move(-speed, getPartialTick());
	// }
}

