#include "IndexBuffer.h"
#include "RenderManager.h"

IndexBuffer::IndexBuffer(std::vector<uint> indices): indices(indices), Buffer(indices.size()) {
}

HRESULT IndexBuffer::init(ID3D11Device* device) {
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.ByteWidth = sizeof(uint) * indices.size();

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = indices.data();
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	return device->CreateBuffer(&desc, &data, buffer.GetAddressOf());
}

void IndexBuffer::push(RenderManager& renderManager) {
	renderManager.getContext()->IASetIndexBuffer(buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}
