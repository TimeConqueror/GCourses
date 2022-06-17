#include "VertexBuffer.h"

#include "Mesh.h"
#include "RenderManager.h"

template <class VERTEX>
VertexBuffer<VERTEX>::VertexBuffer(std::vector<VERTEX> elements):
	Buffer(sizeof(VERTEX) * elements.size()), elements(elements) {
}

template <class VERTEX>
HRESULT VertexBuffer<VERTEX>::init(ID3D11Device* device) {
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.ByteWidth = size;

	D3D11_SUBRESOURCE_DATA data = {}; 
	data.pSysMem = elements.data();
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	return device->CreateBuffer(&desc, &data, buffer.GetAddressOf());
}

template <class VERTEX>
void VertexBuffer<VERTEX>::push(RenderManager& renderManager) {
	uint stride = sizeof(VERTEX);
	UINT offsets[] = {0};
	renderManager.getContext()->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, offsets);
}

template class VertexBuffer<Vertex>;
template class VertexBuffer<PTVertex>;