#include "Katamari.h"

#include "Actor.h"
#include "PlaneComponent.h"
#include "Planet.h"
#include "Player.h"
#include "../Engine/Keyboard.h"
#include "Graphics/Model.h"
#include "Graphics/RenderTypes.h"
#include "Graphics/Renderables/ModelBasedRenderable.h"

Katamari::Katamari(uint screenWidth, uint screenHeight) : Game(L"Katamari", screenWidth, screenHeight)
{
}

RenderableObject plane = PlaneComponent();

Texture skullTexture;
auto skullMesh = Mesh::load("Assets/Skull.obj");
auto skullModel = Model(&RenderTypes::TRIANGLELIST_POS_NORMAL_UV, skullMesh);

void Katamari::init() {
	std::cout << "Initializing..." << std::endl;
	RenderManager& renderManager = getRenderManager();

	renderManager.getCameraHandler()->cameraPos = DirectX::SimpleMath::Vector3(50, 50, 150);

	skullTexture = TextureDefinition(L"Assets/Skull.jpg").bake(renderManager);
	skullModel.init(renderManager);
	renderManager.addRenderable(new Actor(&skullModel, &skullTexture, {}));
	renderManager.addRenderable(&plane);

	player = new Player(&skullModel, &skullTexture, {});
	renderManager.addRenderable(player);
	
}

void Katamari::tick() {
	handleInput();
	dynamic_cast<Player*>(player)->tick();
}

void Katamari::handleInput() {
	if(getInputController().isKeyDown(Keyboard::KEY_F)) {
		getRenderManager().fov = Math::PI_F / 6;
	} else {
		getRenderManager().fov = Math::PI_F / 2;
	}

	if(getInputController().isKeyDown(Keyboard::KEY_C)) {
		getRenderManager().orthographic = !getRenderManager().orthographic;
	}
}

