#pragma once
#include "Shape.h"
#include "VertexBuffer.h"

Shape Shape::quad(float width, float height) {
	return Shape(std::vector<Vertex>(
		             {
			             Vertex(0, 0, 1.0F, 0.0F, 1.0F, 1.0F, 1.0F),
			             Vertex(0, height, 1.0F, 0.0F, 1.0F, 1.0F, 1.0F),
			             Vertex(width, height, 1.0F, 0.0F, 1.0F, 1.0F, 1.0F),
			             Vertex(width, 0, 1.0F, 0.0F, 1.0F, 1.0F, 1.0F)
		             }),
	             std::vector<uint>(
		             {
			             0, 1, 2, 3, 0
		             }));
}

Shape Shape::cube(float width, float height, float depth) {
	return Shape(std::vector<Vertex>(
		             {
			             Vertex(0, 0, 0, 0.0F, 1.0F, 1.0F, 1.0F),
			             Vertex(width, 0, 0, 0.0F, 1.0F, 1.0F, 1.0F),
			             Vertex(width, 0, depth, 0.0F, 1.0F, 1.0F, 1.0F),
			             Vertex(0, 0, depth, 0.0F, 1.0F, 1.0F, 1.0F),
			             Vertex(0, height, 0, 0.0F, 1.0F, 1.0F, 1.0F),
			             Vertex(width, height, 0, 0.0F, 1.0F, 1.0F, 1.0F),
			             Vertex(width, height, depth, 0.0F, 1.0F, 1.0F, 1.0F),
			             Vertex(0, height, depth, 0.0F, 1.0F, 1.0F, 1.0F),
		             }),
	             std::vector<uint>(
		             {
			             0, 1, 2, 0, 2, 3, //y-
			             4, 5, 6, 4, 6, 7, //y+
			             1, 2, 6, 1, 6, 5, //x+
			             0, 3, 7, 0, 7, 4, //x-
			             2, 3, 7, 2, 7, 6, //z+
			             1, 0, 4, 1, 4, 3 //z-
		             }));
}

std::vector<Vertex>& Shape::getVertices() {
	return this->vertices;
}

std::vector<uint>& Shape::getIndexes() {
	return this->indexes;
}
