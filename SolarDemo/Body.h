#pragma once
#include "ITickable.h"
#include "Graphics/RenderableObject.h"

class Body :
    public RenderableObject, public ITickable
{
public:
    DirectX::SimpleMath::Vector3 relPos;
    std::vector<Body*> children;

    Body(RenderType* renderType, Shape& shape)
        : RenderableObject(renderType, shape) {
    }

    Body(RenderType* renderType, Shape&& shape)
        : RenderableObject(renderType, shape) {
    }

    void addChild(Body* body) {
        children.push_back(body);
    }

    void tick() override {
        
    }

    virtual void updatePos(Body* parent) {
        for (const auto child : children) {
            child->updatePos(this);
        }
    }
};

