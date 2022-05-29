#pragma once
#include <directxmath.h>
#include <wrl.h>
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

	Vertex(float x, float y, float z): Vertex(x, y, z, 0.0F, 1.0F, 1.0F, 1.0F) {}

	Vertex(float x, float y): Vertex(x, y, 1.0F) {}
};

template<typename VERTEX>
class VertexBuffer: public Buffer {
private:
	std::vector<VERTEX> elements;
public:
	VertexBuffer(std::vector<VERTEX> elements);

	virtual HRESULT init(ID3D11Device* device) override;
	virtual void push(RenderManager& renderManager) override;
};

