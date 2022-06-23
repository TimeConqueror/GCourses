#pragma once
#include <SimpleMath.h>

#include "BaseRenderable.h"
#include "Graphics/Model.h"
#include "Graphics/Texture.h"

struct Material {
	float ambientFactor = 0.9F;
	float specularFactor = 0.5F;
	float shineFactor = 1.0F;
};

class ModelBasedRenderable : public BaseRenderable
{
private:
	Model* model;
	Texture* texture;
	Material material;

	ConstantBuffer<Material> materialBuffer;
public:
	explicit ModelBasedRenderable(Model* model, Texture* texture, Material material)
		: model(model), texture(texture), material(material) {
	}
	void init(RenderManager& renderManager) override;
	RenderType* getRenderType() const override;
	Texture* getTexture() const;
	Model* getModel() const;
protected:
	void render(RenderManager& renderManager) override;
};

