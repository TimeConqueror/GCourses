#pragma once
#include <SimpleMath.h>

#include "Graphics/ConstantBuffer.h"
#include "Graphics/Renderables/IRenderable.h"

class BaseRenderable : public IRenderable
{
public:
	DirectX::SimpleMath::Vector3 pos;
	ConstantBuffer<DirectX::SimpleMath::Matrix> constantBuffer;
	DirectX::SimpleMath::Matrix transformation = DirectX::SimpleMath::Matrix::Identity;
	void init(RenderManager& renderManager) override;
protected:
	void transform(RenderManager& renderManager, DirectX::SimpleMath::Matrix& data);
	void render(RenderManager& renderManager) override;
};

