#pragma once
#include "ITickable.h"
#include "LocalTransform.h"
#include "MathHelper.h"
#include "Graphics/RenderTypes.h"
#include "Graphics/Renderables/ModelBasedRenderable.h"
#include "Graphics/Renderables/RenderableObject.h"

class Actor : public ModelBasedRenderable, ITickable {
	std::vector<Actor*> children;
public:
	float collisionRadius = 10;
	DirectX::SimpleMath::Vector3 relPos;
	bool bound = false;
	LocalTransform localTransform;

	Actor(Model* model, Texture* texture, const Material& material)
		: ModelBasedRenderable(model, texture, material),
		  localTransform(nullptr) {
		localTransform = LocalTransform(this);
	}

	void tick() override;
	bool addChild(Actor* child);
	void init(RenderManager& renderManager) override;
protected:
	void render(RenderManager& renderManager) override;
	void applyTransformation() override;

	virtual void updatePos(Actor* parent) {
		// if (parent != nullptr) {
		// 	const DirectX::SimpleMath::Vector3 parentPos = parent ? parent->pos : DirectX::SimpleMath::Vector3::Zero;
		//
		// 	//
		// 	//
		// 	//
		// 	// const auto matrix = DirectX::SimpleMath::Matrix::Create
		// 	//
		// 	// const long millis = Math::currentMillis();
		// 	//
		// 	// const double turnProgress = millis % fullTurnTime / static_cast<double>(fullTurnTime);
		// 	// const double turnAngle = Math::PI * 2 * turnProgress;
		// 	//
		// 	// const auto matrix =
		// 	// 	DirectX::SimpleMath::Matrix::CreateFromQuaternion(parent->rotation) * DirectX::SimpleMath::Matrix::CreateTranslation(relPos)
		// 	// 	;
		// 		// DirectX::SimpleMath::Matrix::CreateFromQuaternion(parent->rotation) *
		// 		// ;
		// 	// const auto matrix = DirectX::SimpleMath::Matrix::CreateTranslation(orbitRadius, 0, 0)
		// 	// 	* DirectX::SimpleMath::Matrix::CreateRotationY(turnAngle)
		// 	// 	* DirectX::SimpleMath::Matrix::CreateRotationX(Math::toRadians(orbitTilt))
		// 	// 	* DirectX::SimpleMath::Matrix::CreateRotationY(Math::toRadians(orbitTiltDirection));
		// 	
		// 	// DirectX::SimpleMath::Vector3 relPos = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Zero, matrix);
		// 	//pos = parentPos + relPos;
		// 	//
		// 	// const double rotProgress = millis % selfRotTime / static_cast<double>(selfRotTime);
		// 	// rotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, Math::PI * 2 * rotProgress);
		// 	//
		// }

		// for (const auto child : children) {
		// 	child->updatePos(this);
		// }
	}
};

inline void Actor::tick() {
	if (!this->bound) {
		localTransform.setAbsolutePosition(pos);
		localTransform.setAbsoluteRotation(rotation);
		localTransform.setAbsoluteScale(DirectX::SimpleMath::Vector3(scale, scale, scale));
	}
}

inline bool Actor::addChild(Actor* child) {
	if (child->bound) return false;

	using namespace DirectX::SimpleMath;

	//children.push_back(child);

	Vector3 pos = child->localTransform.getAbsolutePosition();
	Quaternion rotation = child->localTransform.getAbsoluteRotation();
	// const Matrix modelMatrix = this->transformation.Invert();//Transpose?
	// child->pos = Vector3::Transform(child->pos, modelMatrix);
	this->localTransform.addChild(child);
	child->localTransform.setAbsolutePosition(pos);
	child->localTransform.setAbsoluteRotation(rotation);
	child->localTransform.setRelativeScale(Vector3(child->scale, child->scale, child->scale));

	// child->relPos = child->pos - this->pos;
	//
	// child->rotation = child->rotation / this->rotation;

	child->bound = true;
	return true;
}

inline void Actor::init(RenderManager& renderManager) {
	ModelBasedRenderable::init(renderManager);
}

inline void Actor::render(RenderManager& renderManager) {
	ModelBasedRenderable::render(renderManager);

	RenderableObject collisionSphere(&RenderTypes::LINELIST_POS_COLOR, Shape::sphere(collisionRadius, 10, 10, 0xFF00FFFF));
	collisionSphere.init(renderManager);

	collisionSphere.pos = this->localTransform.getAbsolutePosition();
	collisionSphere.rotation = this->localTransform.getAbsoluteRotation();
	collisionSphere.getRenderType()->render(renderManager, collisionSphere);
}

inline void Actor::applyTransformation() {
	// if(!bound) {
	// 	BaseRenderable::applyTransformation();
	// } else {
	// 	
	// }
	transformation *= localTransform.getTransformation();

	// const long millis = Math::currentMillis();
	//
	// const double turnProgress = millis % 10000 / static_cast<double>(10000);
	// const double turnAngle = Math::PI * 2 * turnProgress;

	//transformation *= DirectX::SimpleMath::Matrix::CreateTranslation(0, 0, -15);
	//transformation *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Forward, turnAngle));
}
