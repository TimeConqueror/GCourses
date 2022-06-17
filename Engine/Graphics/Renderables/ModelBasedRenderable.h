#pragma once
#include <SimpleMath.h>

#include "BaseRenderable.h"
#include "Graphics/Model.h"

class ModelBasedRenderable : public BaseRenderable
{
private:
	Model* model;
	DirectX::SimpleMath::Vector3 pos;
public:
	void init(RenderManager& renderManager) override;
	RenderType* getRenderType() const override;
protected:
	void render(RenderManager& renderManager) override;
};

