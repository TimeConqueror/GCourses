#include "Game.h"
#include "Rand.h"
#include <iostream>

Game* Game::instance = nullptr;

Game::Game(LPCWSTR name, uint width, uint height, int ticksPerSecond):
	name(name),
	inputController(InputController(*this)),
	window(inputController, name, width, height),
	renderManager(window),
	timer(ticksPerSecond) {
	CoInitializeEx(nullptr, COINITBASE_MULTITHREADED); // for texture loading

	setInstance(this);
	Rand::init();
};

void Game::initInternals() {
	window.init();

	renderManager.init(this);
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

		inputController.update();
		this->renderManager.render(getPartialTick());

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

InputController& Game::getInputController() {
	return inputController;
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

