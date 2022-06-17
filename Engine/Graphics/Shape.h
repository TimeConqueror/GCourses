#pragma once
#include <array>
#include <map>
#include <SimpleMath.h>
#include <vector>
#include "Utils.h"
#include "VertexBuffer.h"
//TODO remove because of Mesh.h
class Shape {
private:
	std::vector<Vertex> vertices;
	std::vector<uint> indexes;
public:
	Shape(std::vector<Vertex> vertices, std::vector<uint> indexes): vertices(vertices), indexes(indexes) {
	};

	static Shape quad(float width, float height);
	static Shape cube(float width, float height, float depth, int argb);
	static Shape icosphere(uint subdivisions, float scale, int argb);
	static Shape sphere(float radius, int sectorCount, int stackCount, int argb);

	std::vector<Vertex>& getVertices();
	std::vector<uint>& getIndexes();

private:
	static uint vertexForEdge(std::map<std::pair<uint, uint>, uint>& lookup, std::vector<DirectX::SimpleMath::Vector3>& vertices, uint first, uint second);
	static std::vector<uint> subdivide(std::vector<DirectX::SimpleMath::Vector3>& vertices, std::vector<uint> indices);
};
