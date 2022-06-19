#pragma once
#include <vector>
#include <directxmath.h>
#include <SimpleMath.h>
#include "../Utils.h"
#include "Buffer.h"

class RenderManager;

struct Vertex {
	DirectX::XMFLOAT4 pos;
	DirectX::XMFLOAT4 color;

	Vertex(const Vertex& other) = default;
	Vertex(Vertex&& other) noexcept = default;
	Vertex& operator=(const Vertex& other) = default;
	Vertex& operator=(Vertex&& other) noexcept = default;

	Vertex(const DirectX::XMFLOAT4& pos, const DirectX::XMFLOAT4& color)
		: pos(pos),
		  color(color) {
	}

	Vertex(float x, float y, float z, float r, float g, float b, float a):pos(x,y,z, 1.0F), color(r,g,b,a) {

	}

	Vertex(const float x, const float y, const float z): Vertex(x, y, z, 0.0F, 1.0F, 1.0F, 1.0F) {}

	Vertex(const float x, const float y, const float z, const DirectX::SimpleMath::Color& color): Vertex(x, y, z, color.R(), color.G(), color.B(), color.A()) {}

	Vertex(const float x, const float y): Vertex(x, y, 1.0F) {}
};

template<class VERTEX>
class VertexBuffer: public Buffer {
private:
	std::vector<VERTEX> elements;
public:
	VertexBuffer(VertexBuffer&& other) = default;
	VertexBuffer(std::vector<VERTEX> elements);

	virtual HRESULT init(ID3D11Device* device) override;
	void push(RenderManager& renderManager);
};

