#pragma once
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <SimpleMath.h>

#include "Utils.h"

struct PTVertex {
	DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero;
	DirectX::SimpleMath::Vector2 uv = DirectX::SimpleMath::Vector2::Zero;

	PTVertex(const PTVertex& other) = default;
	PTVertex(PTVertex&& other) noexcept = default;
	PTVertex& operator=(const PTVertex& other) = default;
	PTVertex& operator=(PTVertex&& other) noexcept = default;

	PTVertex(const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Vector2& uv)
		: pos(pos),
		uv(uv) {
	}

	PTVertex(float x, float y, float z, float u, float v) :pos(x, y, z), uv(u,v) {

	}

	PTVertex() {}
};

class Mesh
{
private:
	std::vector<PTVertex> vertices;
	std::vector<uint> indexes;
public:
	Mesh(std::vector<PTVertex> vertices, std::vector<uint> indexes) : vertices(vertices), indexes(indexes) {
	};

	std::vector<PTVertex>& getVertices() {
		return vertices;
	}

	std::vector<uint>& getIndexes() {
		return indexes;
	}

	static std::vector<Mesh>& load(const std::string& path) {
		 Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		std::vector<Mesh> meshes;

		if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr) {
			std::cout << importer.GetErrorString() << std::endl;
			return meshes;
		}
		
		processNode(meshes, scene, scene->mRootNode);
		return meshes;
	}

private:
	static void processNode(std::vector<Mesh>& meshes, const aiScene* scene, const aiNode* node) {
		for (uint i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(scene, mesh));
		}
		
		for (uint i = 0; i < node->mNumChildren; i++) {
			processNode(meshes, scene, node->mChildren[i]);
		}
	}
	
	static Mesh processMesh(const aiScene* scene, const aiMesh* mesh) {
		std::vector<PTVertex> vertices;
		std::vector<uint> indices;
	
		for (uint i = 0; i < mesh->mNumVertices; i++) {
			PTVertex vertex;
			vertex.pos = DirectX::SimpleMath::Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		
			if (mesh->mTextureCoords[0] != nullptr) {
				vertex.uv = DirectX::SimpleMath::Vector2(mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y);
			}
			else {
				vertex.uv = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
			}
		
			vertices.push_back(vertex);
		}
		
		for (uint i = 0; i < mesh->mNumFaces; i++) {
			const aiFace face = mesh->mFaces[i];
		
			for (uint j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}
	
		return Mesh(vertices, indices);
	}
};

