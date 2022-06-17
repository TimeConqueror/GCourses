#pragma once
#include "Shape.h"

#include <map>
#include <SimpleMath.h>

#include "MathHelper.h"
#include "VertexBuffer.h"
//TODO remove because of Mesh.h
Shape Shape::quad(float width, float height) {
	return Shape(std::vector(
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

Shape Shape::cube(float width, float height, float depth, int argb) {
	auto color = Math::color(argb);

	return Shape(std::vector(
		             {
			             Vertex(0, 0, 0, color),
			             Vertex(width, 0, 0, color),
			             Vertex(width, 0, depth, color),
			             Vertex(0, 0, depth, color),
			             Vertex(0, height, 0, color),
			             Vertex(width, height, 0, color),
			             Vertex(width, height, depth, color),
			             Vertex(0, height, depth, color),
		             }),
	             std::vector<uint>(
		             {
			             0, 1, 2, 0, 2, 3, //y-
			             4, 5, 6, 4, 6, 7, //y+
			             1, 2, 6, 1, 6, 5, //x+
			             0, 3, 7, 0, 7, 4, //x-
			             2, 3, 7, 2, 7, 6, //z+
			             1, 0, 4, 1, 5, 4 //z-
		             }));
}

Shape Shape::icosphere(uint subdivisions, float scale, int argb) {
	constexpr float x = 0.525731112119133606f;
	constexpr float z = 0.850650808352039932f;
	constexpr float n = 0.f;

	std::vector<DirectX::SimpleMath::Vector3> points = {
		{-x, n, z}, {x, n, z}, {-x, n, -z},
		{x, n, -z}, {n, z, x}, {n, z, -x},
		{n, -z, x}, {n, -z, -x}, {z, x, n},
		{-z, x, n}, {z, -x, n}, {-z, -x, n}
	};

	std::vector<uint> indexes = {
		0, 4, 1, 0, 9, 4, 9, 5, 4, 4, 5, 8, 4, 8, 1,
		8, 10, 1, 8, 3, 10, 5, 3, 8, 5, 2, 3, 2, 7, 3,
		7, 10, 3, 7, 6, 10, 7, 11, 6, 11, 0, 6, 0, 1, 6,
		6, 1, 10, 9, 0, 11, 9, 11, 2, 9, 2, 5, 7, 2, 11
	};

	for (int i = 0; i < subdivisions; ++i) {
		indexes = subdivide(points, indexes);
	}

	size_t size = points.size();
	std::vector<Vertex> vertices;

	for (const auto point : points) {
		vertices.push_back({
			point.x * scale, point.y * scale, point.z * scale, Math::color(argb)
		});
	}

	return Shape(vertices, indexes);
}

Shape Shape::sphere(float radius, int sectorCount, int stackCount, int argb) {
	//http://www.songho.ca/opengl/gl_sphere.html

	std::vector<Vertex> vertices;

	float x, y, z, xy; // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius; // vertex normal
	float s, t; // vertex texCoord

	const float sectorStep = 2 * Math::PI_F / sectorCount;
	const float stackStep = Math::PI_F / stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i) {
		stackAngle = Math::PI_F / 2 - i * stackStep; // starting from pi/2 to -pi/2
		xy = radius * std::cosf(stackAngle); // r * cos(u)
		z = radius * std::sinf(stackAngle); // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j) {
			sectorAngle = j * sectorStep; // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * std::cosf(sectorAngle); // r * cos(u) * cos(v)
			y = xy * std::sinf(sectorAngle); // r * cos(u) * sin(v)

			auto color = Math::color(argb);
			if (sectorCount / 2 > i) {
				color.Negate(color);
			}
			vertices.push_back({x, y, z, color});

			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;

			// vertex tex coord (s, t) range between [0, 1]
			s = static_cast<float>(j) / sectorCount;
			t = static_cast<float>(i) / stackCount;
		}
	}

	// generate CCW index list of sphere triangles
	// k1--k1+1
	// |  / |
	// | /  |
	// k2--k2+1
	std::vector<uint> indices;
	uint k1, k2;
	for (int i = 0; i < stackCount; ++i) {
		k1 = i * (sectorCount + 1); // beginning of current stack
		k2 = k1 + sectorCount + 1; // beginning of next stack

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0) {
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1)) {
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}

	return Shape(vertices, indices);
}

std::vector<Vertex>& Shape::getVertices() {
	return this->vertices;
}

std::vector<uint>& Shape::getIndexes() {
	return this->indexes;
}

uint Shape::vertexForEdge(std::map<std::pair<uint, uint>, uint>& lookup,
                          std::vector<DirectX::SimpleMath::Vector3>& vertices, uint first, uint second) {
	std::map<std::pair<uint, uint>, uint>::key_type key(first, second);

	if (key.first > key.second) {
		std::swap(key.first, key.second);
	}

	const auto inserted = lookup.insert({
		key, vertices.size()
	});

	if (inserted.second) {
		DirectX::SimpleMath::Vector3& edge0 = vertices[first];
		DirectX::SimpleMath::Vector3& edge1 = vertices[second];
		DirectX::SimpleMath::Vector3 point = (edge0 + edge1);
		point.Normalize();
		vertices.push_back(point);
	}

	return inserted.first->second;
}

std::vector<uint> Shape::subdivide(std::vector<DirectX::SimpleMath::Vector3>& vertices, std::vector<uint> indices) {
	std::map<std::pair<uint, uint>, uint> lookup;
	std::vector<uint> result;

	for (int i = 0; i < indices.size(); i += 3) {
		std::array triangle = {
			indices[i],
			indices[i + 1],
			indices[i + 2]
		};

		std::array<int, 3> mid;

		for (int edge = 0; edge < 3; ++edge) {
			mid[edge] = vertexForEdge(
				lookup,
				vertices,
				triangle[edge],
				triangle[(edge + 1) % 3]);
		}

		result.push_back(triangle[0]);
		result.push_back(mid[0]);
		result.push_back(mid[2]);

		result.push_back(triangle[1]);
		result.push_back(mid[1]);
		result.push_back(mid[0]);

		result.push_back(triangle[2]);
		result.push_back(mid[2]);
		result.push_back(mid[1]);

		result.push_back(mid[0]);
		result.push_back(mid[1]);
		result.push_back(mid[2]);
	}

	return result;
}
