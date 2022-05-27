#include "PlaneComponent.h"

PlaneComponent::PlaneComponent(): RenderableObject(lineGrid(50, 10, 1000)) {

}

Shape PlaneComponent::lineGrid(int size, int lineCount, int lineWidth) {
	std::vector<Vertex> vertices;
	std::vector<uint> indexes;

	for (int i = 0; i < lineCount; ++i) {
		vertices.push_back(Vertex(i * size, 0, 0, 0, 1, 1, 1));
		vertices.push_back(Vertex(i * size, 0, lineWidth, 0, 1, 1, 1));
		vertices.push_back(Vertex(0, 0, i * size, 0, 1, 1, 1));
		vertices.push_back(Vertex(lineWidth, 0, i * size, 0, 1, 1, 1));

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(3);
	}

	return Shape(vertices, indexes);
}
