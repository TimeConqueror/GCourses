#pragma once
#include <iostream>
#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <SimpleMath.h>

#include "Utils.h"

struct PTVertex {
	DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero;
	DirectX::SimpleMath::Vector3 normal = DirectX::SimpleMath::Vector3::Zero;
	DirectX::SimpleMath::Vector2 uv = DirectX::SimpleMath::Vector2::Zero;

	PTVertex(const PTVertex& other) = default;
	PTVertex(PTVertex&& other) noexcept = default;
	PTVertex& operator=(const PTVertex& other) = default;
	PTVertex& operator=(PTVertex&& other) noexcept = default;

	PTVertex() {
	}
};

class Mesh {
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

	static std::vector<Mesh> load(const std::string& path) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_FlipWindingOrder);

		std::vector<Mesh> meshes;

		if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr) {
			std::cout << importer.GetErrorString() << std::endl;
			return meshes;
		}

		parseNode(meshes, scene, scene->mRootNode);
		return meshes;
	}

private:
	static void parseNode(std::vector<Mesh>& meshes, const aiScene* scene, const aiNode* node) {
		for (uint i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(parseMesh(mesh));
		}

		for (uint i = 0; i < node->mNumChildren; i++) {
			parseNode(meshes, scene, node->mChildren[i]);
		}
	}

	static Mesh parseMesh(const aiMesh* mesh) {
		std::vector<PTVertex> vertices;
		std::vector<uint> indices;

		for (uint i = 0; i < mesh->mNumVertices; i++) {
			PTVertex vertex;
			vertex.pos = DirectX::SimpleMath::Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

			if (mesh->mTextureCoords[0] != nullptr) {
				vertex.uv = DirectX::SimpleMath::Vector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			}

			if (mesh->HasNormals()) {
				vertex.normal = DirectX::SimpleMath::Vector3{
					mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z
				};
			}

			vertices.push_back(vertex);
		}

		for (uint i = 0; i < mesh->mNumFaces; i++) {
			const auto face = mesh->mFaces[i];

			for (uint j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		return Mesh(vertices, indices);
	}
};
