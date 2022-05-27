#include "SolarDemo.h"

#include "PlaneComponent.h"
#include "../Engine/Keyboard.h"

SolarDemo::SolarDemo(uint screenWidth, uint screenHeight) : Game(L"SolarDemo", screenWidth, screenHeight)
{
}

RenderableObject bom = PlaneComponent();

void SolarDemo::init() {
	std::cout << "Initializing..." << std::endl;
	RenderManager& renderManager = getRenderManager();

	renderManager.addRenderable("left_paddle", bom);
}

void SolarDemo::tick() {
}

void SolarDemo::handleWinState() {
}

void SolarDemo::handleInput() {
}

