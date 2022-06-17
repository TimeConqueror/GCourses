#include "SolarDemo.h"

#include "PlaneComponent.h"
#include "Planet.h"
#include "../Engine/Keyboard.h"
#include "Graphics/RenderTypes.h"
#include "Graphics/Shape.h"

SolarDemo::SolarDemo(uint screenWidth, uint screenHeight) : Game(L"SolarDemo", screenWidth, screenHeight)
{
}

RenderableObject plane = PlaneComponent();
Planet sun = Planet(&RenderTypes::TRIANGLELIST_POS_COLOR, Shape::sphere(100, 50, 50, 0x5522FF00), DirectX::SimpleMath::Vector3(-2, 3, 1), 10000, 1, 1, 1, 1);
Planet earth = Planet(&RenderTypes::TRIANGLELIST_POS_COLOR, Shape::cube(10, 10, 10, 0xFF00FF00), DirectX::SimpleMath::Vector3(2, 10, 1), 2000, 200.0F, 10000, 80, 20);
Planet moon = Planet(&RenderTypes::TRIANGLELIST_POS_COLOR, Shape::sphere(5, 50, 50, 0xFFFFFFFF), DirectX::SimpleMath::Vector3::Up, 1000, 20.0F, 5000, 10, 10);
Planet parent = Planet(&RenderTypes::TRIANGLELIST_POS_COLOR, Shape::icosphere(0, 40, 0xFF0000FF), DirectX::SimpleMath::Vector3::Down, 3000, 400.0F, 40000, 10, 20);
Planet parentChild = Planet(&RenderTypes::TRIANGLELIST_POS_COLOR, Shape::cube(15, 15, 15, 0xFF00D4FF), DirectX::SimpleMath::Vector3::Left, 4000, 150.0F, 20000, 10, 20);
Planet parentChildChild = Planet(&RenderTypes::TRIANGLELIST_POS_COLOR, Shape::sphere(7, 50, 50, 0xFFF0FF0F), DirectX::SimpleMath::Vector3::Right, 5000, 60.0F, 10000, 10, 20);
Planet parentChildChildChild1 = Planet(&RenderTypes::TRIANGLELIST_POS_COLOR, Shape::sphere(5, 50, 50, 0xFF44FFFF), DirectX::SimpleMath::Vector3::Backward, 3000, 24.0F, 1000, 20, 10);
Planet parentChildChildChild2 = Planet(&RenderTypes::TRIANGLELIST_POS_COLOR, Shape::sphere(6, 50, 50, 0x00AAAAFF), DirectX::SimpleMath::Vector3::Forward, 1000, 17.0F, 500, 40, 90);

void SolarDemo::init() {
	std::cout << "Initializing..." << std::endl;
	RenderManager& renderManager = getRenderManager();

	renderManager.addRenderable(&plane);
	renderManager.addRenderable(&sun);
	renderManager.addRenderable(&earth);
	renderManager.addRenderable(&moon);
	//renderManager.addRenderable("zzz", zom);
	//renderManager.addRenderable("sphrer", ñom);

	renderManager.addRenderable(&parent);
	renderManager.addRenderable(&parentChild);
	renderManager.addRenderable(&parentChildChild);
	renderManager.addRenderable(&parentChildChildChild1);
	renderManager.addRenderable(&parentChildChildChild2);

	renderManager.getCameraHandler()->cameraPos = DirectX::SimpleMath::Vector3(50, 50, 150);

	sun.addChild(&earth);
	earth.addChild(&moon);

	sun.addChild(&parent);
	parent.addChild(&parentChild);
	parentChild.addChild(&parentChildChild);
	parentChildChild.addChild(&parentChildChildChild1);
	parentChildChild.addChild(&parentChildChildChild2);

	sun.pos = DirectX::SimpleMath::Vector3(500, 500, 500);
}

void SolarDemo::addPlanet(Planet* planet) {
	auto renderManager = getRenderManager();
	renderManager.addRenderable(planet);
	//entities.push_back(planet);
}

void SolarDemo::tick() {
	sun.updatePos(nullptr);

	handleInput();
}

void SolarDemo::handleWinState() {
}

void SolarDemo::handleInput() {
	if(getInputController().isKeyDown(Keyboard::KEY_F)) {
		getRenderManager().fov = Math::PI_F / 6;
	} else {
		getRenderManager().fov = Math::PI_F / 2;
	}

	if(getInputController().isKeyDown(Keyboard::KEY_C)) {
		getRenderManager().orthographic = !getRenderManager().orthographic;
	}
}

