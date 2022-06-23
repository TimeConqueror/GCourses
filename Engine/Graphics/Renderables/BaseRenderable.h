#pragma once
#include <SimpleMath.h>

#include "Graphics/ConstantBuffer.h"
#include "Graphics/Renderables/IRenderable.h"

struct Transform {
	DirectX::SimpleMath::Matrix worldTransform;
	DirectX::SimpleMath::Matrix worldProjTransform;
	DirectX::SimpleMath::Matrix invertedTransposedWorldTransform;
};

class BaseRenderable : public IRenderable
{
public:
	DirectX::SimpleMath::Vector3 pos;
	float scale = 1;
	DirectX::SimpleMath::Quaternion rotation;

	ConstantBuffer<Transform> constantBuffer;
	DirectX::SimpleMath::Matrix transformation = DirectX::SimpleMath::Matrix::Identity;
	void init(RenderManager& renderManager) override;
protected:
	void transform(RenderManager& renderManager, Transform& data);
	void render(RenderManager& renderManager) override;

	virtual void applyTransformation();
};

