#pragma once
#include <vector>
#include "Utils.h"
#include "VertexBuffer.h"

class Shape {
private:
	std::vector<Vertex> vertices;
	std::vector<uint> indexes;
public:
	Shape(std::vector<Vertex> vertices, std::vector<uint> indexes): vertices(vertices), indexes(indexes) {};

	static Shape quad(float width, float height);

	std::vector<Vertex>& getVertices();
	std::vector<uint>& getIndexes();
};

