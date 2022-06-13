#include "Pong.h"
#include "../Engine/Keyboard.h"

void Pong::init() {
	RenderManager& renderManager = getRenderManager();
	std::cout << "Initializing..." << std::endl;
	renderManager.addRenderable(&leftBoard);
	renderManager.addRenderable(&rightBoard);
	renderManager.addRenderable(&ball);

	ball.reset();
}

void Pong::tick() {
	handleInput();

	if (paused) return;

	ball.tick(leftBoard, rightBoard, getPartialTick());

	handleWinState();
}

void Pong::handleWinState() {
	WinState winState = ball.checkWin();
	if (winState == WinState::PLAYING) {
		return;
	}

	if (winState == WinState::LEFT_WON) {
		std::cout << "Player on the Left Side won the round!" << std::endl;
		leftScore++;
	} else {
		std::cout << "Player on the Right Side won the round!" << std::endl;
		rightScore++;
	}

	std::cout << "Scores: " << leftScore << ":" << rightScore << std::endl;

	leftBoard.reset();
	rightBoard.reset();

	ball.reset(winState == WinState::LEFT_WON);
}

void Pong::handleInput() {
	InputController& inputController = getInputController();

	if (inputController.isKeyDown(Keyboard::KEY_SPACE)) {
		paused = !paused;
	}

	if (paused) return;

	float speed = 0.05F;
	if(inputController.isKeyDown(Keyboard::KEY_W)) {
		leftBoard.move(speed, getPartialTick());
	} else if (inputController.isKeyDown(Keyboard::KEY_S)) {
		leftBoard.move(-speed, getPartialTick());
	} else if (inputController.isKeyDown(Keyboard::KEY_ARROW_UP)) {
		rightBoard.move(speed, getPartialTick());
	} else if (inputController.isKeyDown(Keyboard::KEY_ARROW_DOWN)) {
		rightBoard.move(-speed, getPartialTick());
	}
}

