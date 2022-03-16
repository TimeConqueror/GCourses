#pragma once
#include "..\Engine\Graphics\RenderableObject.h"
#include "../Engine/Graphics/Shape.h"

class Board :
	public RenderableObject {
private:
	const float width;
	const float height;
	const bool left;
public:
	static const float ratioX;
	static const float ratioY;

	Board(bool isLeft): RenderableObject(Shape::quad(ratioX, ratioY)), width(ratioX), height(ratioY), left(isLeft) {
		reset();
	}

	float getWidth() const;
	float getHeight() const;

	void move(float amount, float partialTick);
	void reset();
};

