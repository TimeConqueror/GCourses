#pragma once

//#include <winerror.h>
#include <vector>

#include "IndexBuffer.h"
#include "Mesh.h"
#include "RenderType.h"
#include "VertexBuffer.h"

class RenderManager;

class Model {
private:
	std::vector<Mesh>& meshes;
	std::vector<VertexBuffer<PTVertex>> vertexBuffers;
	std::vector<IndexBuffer> indexBuffers;
	RenderType* renderType;
public:
	Model(RenderType* renderType, std::vector<Mesh>& meshes)
		: meshes(meshes), renderType(renderType) {
		for (Mesh mesh : meshes)  {
			vertexBuffers.push_back(VertexBuffer<PTVertex>(mesh.getVertices()));
			indexBuffers.push_back(IndexBuffer(mesh.getIndexes()));
		}
	}

	void init(RenderManager& renderManager);
	void render(RenderManager& renderManager);
	RenderType* getRenderType() const;
};
