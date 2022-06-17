#pragma once
class RenderManager;
class RenderType;

class IRenderable
{
public:
	virtual void init(RenderManager& renderManager) = 0;
	virtual void render(RenderManager& renderManager) = 0;
	virtual RenderType* getRenderType() const = 0;
	virtual ~IRenderable() = default;
};

