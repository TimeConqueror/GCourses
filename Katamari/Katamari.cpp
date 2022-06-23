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
Texture bananaTexture;
Texture appleTexture;
auto skullMesh = Mesh::load("Assets/Skull.obj");
auto bananaMesh = Mesh::load("Assets/Banana.obj");
auto appleMesh = Mesh::load("Assets/Apple.obj");
auto skullModel = Model(&RenderTypes::TRIANGLELIST_POS_NORMAL_UV, skullMesh);
auto bananaModel = Model(&RenderTypes::TRIANGLELIST_POS_NORMAL_UV, bananaMesh);
auto appleModel = Model(&RenderTypes::TRIANGLELIST_POS_NORMAL_UV, appleMesh);

Actor* banana1;
Actor* banana2;
Actor* apple1;

void Katamari::init() {
	std::cout << "Initializing..." << std::endl;
	RenderManager& renderManager = getRenderManager();

	renderManager.getCameraHandler()->cameraPos = DirectX::SimpleMath::Vector3(50, 50, 150);

	skullTexture = TextureDefinition(L"Assets/Skull.jpg").bake(renderManager);
	bananaTexture = TextureDefinition(L"Assets/Banana.png").bake(renderManager);
	appleTexture = TextureDefinition(L"Assets/Apple.png").bake(renderManager);
	skullModel.init(renderManager);
	bananaModel.init(renderManager);
	appleModel.init(renderManager);
	banana1 = new Actor(&bananaModel, &bananaTexture, {});
	banana2 = new Actor(&bananaModel, &bananaTexture, {});
	apple1 = new Actor(&appleModel, &appleTexture, {});
	addActor(banana1, 100, 0, 10, 10);
	addActor(banana2, -100, 0, 17, 15);
	addActor(apple1, 100, 100, 0.5, 20);
	renderManager.addRenderable(new Actor(&skullModel, &skullTexture, {}));
	renderManager.addRenderable(&plane);

	player = new Player(&skullModel, &skullTexture, {});
	static_cast<Actor*>(player)->collisionRadius = 12;
	renderManager.addRenderable(player);
}

void Katamari::addActor(Actor* actor, float x, float z, float scale, float collisionRadius) {
	this->entities.push_back(actor);
	actor->pos = DirectX::SimpleMath::Vector3(x, 0, z);
	actor->scale = scale;
	actor->collisionRadius = collisionRadius;
	getRenderManager().addRenderable(actor);
}


void Katamari::tick() {
	handleInput();
	dynamic_cast<Player*>(player)->tick();
	for (Actor* entity : entities) {
		entity->tick();
	}
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

