#include "VertexBuffer.h"
#include "RenderManager.h"

VertexBuffer::VertexBuffer(std::vector<Vertex> elements):
	elements(elements), Buffer(elements.size()) {
}

HRESULT VertexBuffer::init(ID3D11Device* device) {
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.ByteWidth = sizeof(Vertex) * size;

	D3D11_SUBRESOURCE_DATA data = {}; 
	data.pSysMem = elements.data();
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	return device->CreateBuffer(&desc, &data, buffer.GetAddressOf());
}

void VertexBuffer::push(RenderManager& renderManager) {
	uint stride = sizeof(Vertex);
	UINT offsets[] = {0};
	renderManager.getContext()->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, offsets);
}
