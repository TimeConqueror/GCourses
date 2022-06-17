#pragma once
#include "..\Engine\Graphics\Renderables\RenderableObject.h"
#include "../Engine/Graphics/Shape.h"
#include "Graphics/RenderTypes.h"

class Board :
	public RenderableObject {
private:
	const float width;
	const float height;
	const bool left;
public:
	static const float ratioX;
	static const float ratioY;

	Board(bool isLeft): RenderableObject(&RenderTypes::TRIANGLELIST_POS_COLOR, Shape::quad(ratioX, ratioY)), width(ratioX), height(ratioY), left(isLeft) {
		reset();
	}

	float getWidth() const;
	float getHeight() const;

	void move(float amount, float partialTick);
	void reset();
};

