#include "LocalTransform.h"
#include "Actor.h"

DirectX::SimpleMath::Quaternion LocalTransform::getAbsoluteRotation() const {
	return parent ? relRotation * parent->localTransform.getAbsoluteRotation() : relRotation;
}

void LocalTransform::setAbsoluteScale(DirectX::SimpleMath::Vector3 scale) {
	relScale = parent ? scale / parent->localTransform.getAbsoluteScale() : scale;
}

void LocalTransform::setAbsoluteRotation(DirectX::SimpleMath::Quaternion rotation) {
	relRotation = parent ? rotation / parent->localTransform.getAbsoluteRotation() : rotation;

	if(parent) {
		DirectX::SimpleMath::Quaternion q;
		parent->localTransform.getAbsoluteRotation().Inverse(q);
		relRotation = q * rotation;
	} else {
		relRotation = rotation;
	}
}

DirectX::SimpleMath::Vector3 LocalTransform::getAbsolutePosition() const {
	if (parent == nullptr) return relPosition;
	const DirectX::SimpleMath::Matrix model = parent->localTransform.getTransformation();
	return DirectX::SimpleMath::Vector3::Transform(relPosition, model);
}

void LocalTransform::setAbsolutePosition(DirectX::SimpleMath::Vector3 position) {
	if (parent != nullptr) {
		const DirectX::SimpleMath::Matrix world = parent->localTransform.getTransformation().Invert();
		relPosition = DirectX::SimpleMath::Vector3::Transform(position, world);
	}
	else {
		relPosition = position;
	}
}

DirectX::SimpleMath::Matrix LocalTransform::getTransformation() const {
	DirectX::SimpleMath::Matrix model = DirectX::SimpleMath::Matrix::CreateScale(relScale)
		* DirectX::SimpleMath::Matrix::CreateFromQuaternion(relRotation)
		* DirectX::SimpleMath::Matrix::CreateTranslation(relPosition);

	if (parent != nullptr) {
		model *= parent->localTransform.getTransformation();
	}

	return model;
}

void LocalTransform::addChild(Actor* child) {
	LocalTransform& childTransform = child->localTransform;
	childTransform.parent = owner;
	children.push_back(child);
}
