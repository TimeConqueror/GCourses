#include "Game.h"
#include <iostream>

Game* Game::instance = nullptr;

Game::Game(LPCWSTR name, uint width, uint height, int ticksPerSecond):
	name(name),
	inputController(InputController(*this)),
	window(inputController, name, width, height),
	renderManager(window),
	timer(ticksPerSecond) {

	setInstance(this);
};

void Game::initInternals() {
	window.init();

	try {
		renderManager.init();
	} catch (RenderException& e) {
		throw std::runtime_error("Render System Initialization Error. Error Code: " + e.errorCode);
	}
}

void Game::run() {
	initInternals();
	init();

	timer.start();

	MSG msg = {};
	bool shouldExit = false;
	while (!shouldExit) {
		// Handle the windows messages.
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		int ticks = timer.advanceTime();
		for (int i = 0; i < std::min<int>(10, ticks); i++) {
			this->tick();
		}

		this->renderManager.render();

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT) {
			shouldExit = true;
		}
	}
}

bool Game::isReady() {
	return instance != nullptr;
}

float Game::getPartialTick() {
	return timer.getPartialTick();
}

Window& Game::getWindow() {
	return window;
}

RenderManager& Game::getRenderManager() {
	return renderManager;
}

Game* Game::getInstance() {
	if (instance == nullptr)
		throw std::runtime_error("The game has not been created yet");
	return instance;
}

void Game::setInstance(Game* game) {
	if (instance != nullptr) {
		throw std::runtime_error("Instance was already defined");
	}

	instance = game;
}

