#pragma once
#include "Graphics/Shape.h"
#include "Graphics/Renderables/RenderableObject.h"

class PlaneComponent : public RenderableObject {
public:
	PlaneComponent();

	static Shape lineGrid(int size, int gridSize);
};
