#pragma once
#include "..\Engine\Graphics\RenderableObject.h"

class RenderManager;

class Board :
	public RenderableObject {
private:
	static const float ratioX;
	static const float ratioY;

	const float width;
	const float height;

	float x = 0;
	float y = 0;
public:
	Board(bool isLeft): RenderableObject(
		std::vector<Vertex>({
		Vertex(0, 0, 1.0F, 0.0F, 1.0F, 1.0F, 1.0F),
		Vertex(0, ratioY, 1.0F, 0.0F, 1.0F, 1.0F, 1.0F),
		Vertex(ratioX, ratioY, 1.0F, 0.0F, 1.0F, 1.0F, 1.0F),
		Vertex(ratioX, 0, 1.0F, 0.0F, 1.0F, 1.0F, 1.0F)
							}),
		std::vector<uint>({
			2,0,1,3,0,2
						  })), width(ratioX), height(ratioY) {
		setX(isLeft ? -1 + 0.01F : 1 - width - 0.01F);
		setY(-height/2);
	}

	float getWidth() const;
	float getHeight() const;
private:
};

