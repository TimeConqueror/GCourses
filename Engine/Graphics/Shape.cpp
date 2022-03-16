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
		2,0,1,3,0,2
			}));
}

std::vector<Vertex>& Shape::getVertices() {
	return this->vertices;
}

std::vector<uint>& Shape::getIndexes() {
	return this->indexes;
}