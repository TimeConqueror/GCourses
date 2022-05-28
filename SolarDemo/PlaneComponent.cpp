#include "PlaneComponent.h"

PlaneComponent::PlaneComponent(): RenderableObject(lineGrid(100, 50)) {

}

Shape PlaneComponent::lineGrid(int step, int gridSize) {
	std::vector<Vertex> vertices = std::vector<Vertex>(
		{
			Vertex(0, 0, 0, 1.0F, 0.0F, 0.0F, 1.0F),
			Vertex(100, 0, 0, 1.0F, 0.0F, 0.0F, 1.0F),
			Vertex(0, 0, 0, 0.0F, 1.0F, 0.0F, 1.0F),
			Vertex(0, 100, 0, 0.0F, 1.0F, 0.0F, 1.0F),
			Vertex(0, 0, 0, 0.0F, 0.0F, 1.0F, 1.0F),
			Vertex(0, 0, 100, 0.0F, 0.0F, 1.0F, 1.0F),
		});
	std::vector<uint> indexes;

	int index = 6;
	
	for (int i = 0; i < gridSize; ++i) {
		vertices.push_back(Vertex((-gridSize / 2.0F + i) * step, 0, -gridSize / 2.0F * step, 242 / 255.0F, 0, 1, 1));
		vertices.push_back(Vertex((-gridSize / 2.0F + i) * step, 0, gridSize / 2.0F * step, 242 / 255.0F, 0, 1, 1));
		vertices.push_back(Vertex(-gridSize / 2.0F * step, 0, (-gridSize / 2.0F + i) * step, 242 / 255.0F, 0, 1, 1));
		vertices.push_back(Vertex(gridSize / 2.0F * step, 0, (-gridSize / 2.0F + i) * step, 242 / 255.0F, 0, 1, 1));
	
		indexes.push_back(index++);
		indexes.push_back(index++);
		indexes.push_back(index++);
		indexes.push_back(index++);
	}

	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);
	indexes.push_back(3);
	indexes.push_back(4);
	indexes.push_back(5);

	return Shape(vertices, indexes);
}
