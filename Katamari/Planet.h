#pragma once
#include "Body.h"
#include "ITickable.h"
#include "MathHelper.h"

class Planet :
    public Body, public ITickable
{
private:
    DirectX::SimpleMath::Vector3 axis;
    //in ms
    long selfRotTime;

    float orbitRadius;
    // in ms
    long fullTurnTime;
    //in degrees
    float orbitTilt;
    // in degrees
    float orbitTiltDirection;

public:
    Planet(RenderType* renderType, Shape& shape, const DirectX::SimpleMath::Vector3& axis, long selfRotTime,
        float orbitRadius, long fullTurnTime, float orbitTilt, float orbitTiltDirection)
        : Body(renderType, shape),
          axis(axis),
          selfRotTime(selfRotTime),
          orbitRadius(orbitRadius),
          fullTurnTime(fullTurnTime),
          orbitTilt(orbitTilt),
          orbitTiltDirection(orbitTiltDirection) {
    }

    Planet(RenderType* renderType, Shape&& shape, const DirectX::SimpleMath::Vector3& axis, long selfRotTime,
        float orbitRadius, long fullTurnTime, float orbitTilt, float orbitTiltDirection)
        : Body(renderType, shape),
          axis(axis),
          selfRotTime(selfRotTime),
          orbitRadius(orbitRadius),
          fullTurnTime(fullTurnTime),
          orbitTilt(orbitTilt),
          orbitTiltDirection(orbitTiltDirection) {
    }

    void tick() override;

    void updatePos(Body* parent) override {
        const DirectX::SimpleMath::Vector3 parentPos = parent ? parent->pos : DirectX::SimpleMath::Vector3(1000, 1000, 1000);

        const long millis = Math::currentMillis();

        const double turnProgress = millis % fullTurnTime / static_cast<double>(fullTurnTime);
        const double turnAngle = Math::PI * 2 * turnProgress;

        const auto matrix = DirectX::SimpleMath::Matrix::CreateTranslation(orbitRadius, 0, 0)
        * DirectX::SimpleMath::Matrix::CreateRotationY(turnAngle)
        * DirectX::SimpleMath::Matrix::CreateRotationX(Math::toRadians(orbitTilt))
        * DirectX::SimpleMath::Matrix::CreateRotationY(Math::toRadians(orbitTiltDirection));

        DirectX::SimpleMath::Vector3 relPos = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Zero, matrix);
        pos = parentPos + relPos;

        const double rotProgress = millis % selfRotTime / static_cast<double>(selfRotTime);
        rotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, Math::PI * 2 * rotProgress);

        Body::updatePos(this);
    }
};

