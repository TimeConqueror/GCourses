#include "SolarDemo.h"

#include "PlaneComponent.h"
#include "../Engine/Keyboard.h"
#include "Graphics/RenderTypes.h"

SolarDemo::SolarDemo(uint screenWidth, uint screenHeight) : Game(L"SolarDemo", screenWidth, screenHeight)
{
}

RenderableObject bom = PlaneComponent();
RenderableObject zom = RenderableObject(&RenderTypes::TRIANGLELIST_POS_COLOR, Shape::cube(100, 100, 150));

void SolarDemo::init() {
	std::cout << "Initializing..." << std::endl;
	RenderManager& renderManager = getRenderManager();

	renderManager.addRenderable("left_paddle", bom);
	renderManager.addRenderable("zzz", zom);

	renderManager.getCameraHandler()->cameraPos = DirectX::SimpleMath::Vector3(50, 50, 150);
}

void SolarDemo::tick() {
}

void SolarDemo::handleWinState() {
}

void SolarDemo::handleInput() {
}

