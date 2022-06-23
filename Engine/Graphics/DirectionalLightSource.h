#pragma once
#include <SimpleMath.h>

#include "ShadowMap.h"
#include "Renderables/ModelBasedRenderable.h"
class RenderManager;
class BaseRenderable;

class DirectionalLightSource
{
public:
	DirectX::SimpleMath::Vector3 direction;
	DirectX::SimpleMath::Vector3 color;
private:
	ShadowMap shadowMap;
public:
	//DirectX::SimpleMath::Matrix calcViewProjForRenderable() const;
	void init(RenderManager* renderManager);
	void pushShadowMapTexture(RenderManager* renderManager, uint slot);
	ShadowMap& getShadowMap() {
		return shadowMap;
	}

	DirectX::SimpleMath::Matrix calcViewProjForRenderable(BaseRenderable* modelBasedRenderable);
};

