#include "SolarDemo.h"

#include "PlaneComponent.h"
#include "Planet.h"
#include "../Engine/Keyboard.h"
#include "Graphics/RenderTypes.h"

SolarDemo::SolarDemo(uint screenWidth, uint screenHeight) : Game(L"SolarDemo", screenWidth, screenHeight)
{
}

RenderableObject plane = PlaneComponent();
Body sun = Body(&RenderTypes::TRIANGLELIST_POS_COLOR, Shape::sphere(50, 50, 50, 0x00FFFF00));
Planet earth = Planet(&RenderTypes::TRIANGLELIST_POS_COLOR, Shape::cube(10, 10, 10, 0xFF00FF00), DirectX::SimpleMath::Vector3::One, 100.0F, 5000, 45, 90);
Planet moon = Planet(&RenderTypes::TRIANGLELIST_POS_COLOR, Shape::sphere(10, 50, 50, 0xFFFFFFFF), DirectX::SimpleMath::Vector3::One, 100.0F, 10000, 0, 0);

void SolarDemo::init() {
	std::cout << "Initializing..." << std::endl;
	RenderManager& renderManager = getRenderManager();

	renderManager.addRenderable("plane", plane);
	renderManager.addRenderable("sun", sun);
	renderManager.addRenderable("earth", earth);
	renderManager.addRenderable("moon", moon);
	//renderManager.addRenderable("zzz", zom);
	//renderManager.addRenderable("sphrer", ñom);

	renderManager.getCameraHandler()->cameraPos = DirectX::SimpleMath::Vector3(50, 50, 150);

	sun.addChild(&earth);
	earth.addChild(&moon);
}

void SolarDemo::addPlanet(Planet* planet) {
	auto renderManager = getRenderManager();
	renderManager.addRenderable(std::to_string(entities.size()), *planet);
	//entities.push_back(planet);
}

void SolarDemo::tick() {
	sun.updatePos(nullptr);
}

void SolarDemo::handleWinState() {
}

void SolarDemo::handleInput() {
}

