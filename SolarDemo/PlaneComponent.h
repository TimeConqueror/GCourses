#pragma once
#include "Graphics/RenderableObject.h"

class PlaneComponent : public RenderableObject {
public:
	PlaneComponent();

	static Shape lineGrid(int size, int gridSize);
};
