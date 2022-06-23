#pragma once
#include <vector>
#include <SimpleMath.h>


class Actor;

class LocalTransform
{
private:
	Actor* parent;
	Actor* owner;
	std::vector<Actor*> children;

	DirectX::SimpleMath::Quaternion relRotation = DirectX::SimpleMath::Quaternion::Identity;
	DirectX::SimpleMath::Vector3 relPosition;
	DirectX::SimpleMath::Vector3 relScale = DirectX::SimpleMath::Vector3::One;
public:
	LocalTransform(Actor* owner)
		: parent(nullptr), owner(owner)
	{}

	void setRelativeRotation(DirectX::SimpleMath::Quaternion relativeRotation) {
		relRotation = relativeRotation;
	}

	void setRelativePosition(DirectX::SimpleMath::Vector3 relativePosition) {
		relPosition = relativePosition;
	}

	void setRelativeScale(DirectX::SimpleMath::Vector3 relativeScale) {
		relScale = relativeScale;
	}

	void setAbsoluteScale(DirectX::SimpleMath::Vector3 scale);
	void setAbsoluteRotation(DirectX::SimpleMath::Quaternion rotation);
	void setAbsolutePosition(DirectX::SimpleMath::Vector3 position);

	DirectX::SimpleMath::Quaternion getAbsoluteRotation() const;
	DirectX::SimpleMath::Vector3 getAbsolutePosition() const;
	DirectX::SimpleMath::Matrix getTransformation() const;

	DirectX::SimpleMath::Vector3 getAbsoluteScale() const {
		return relScale;
	}

	DirectX::SimpleMath::Vector3 getRelativePosition() const {
		return relPosition;
	}

	DirectX::SimpleMath::Quaternion getRelativeRotation() const {
		return relRotation;
	}

	Actor* getParent() const {
		return parent;
	}

	bool hasParent() const {
		return parent != nullptr;
	}

	void addChild(Actor* child);
};

