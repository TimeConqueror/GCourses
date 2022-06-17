#pragma once
#include <SimpleMath.h>

#include "BaseRenderable.h"
#include "Graphics/Model.h"
#include "Graphics/Texture.h"

class ModelBasedRenderable : public BaseRenderable
{
private:
	Model* model;
	Texture* texture;
	DirectX::SimpleMath::Vector3 pos;
public:
	explicit ModelBasedRenderable(Model* model, Texture* texture)
		: model(model), texture(texture) {
	}
	void init(RenderManager& renderManager) override;
	RenderType* getRenderType() const override;
protected:
	void render(RenderManager& renderManager) override;
};

