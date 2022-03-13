#include "ConstantBuffer.h"
#include "RenderManager.h"

//constant buffer is only 16-byte aligned?
ConstantBuffer::ConstantBuffer(): Buffer(sizeof(ConstantBufferData) + (16 - sizeof(ConstantBufferData) % 16)) {

}

HRESULT ConstantBuffer::init(ID3D11Device* device) {
	D3D11_BUFFER_DESC desc = {};

	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.ByteWidth = size;
	return device->CreateBuffer(&desc, 0, buffer.GetAddressOf());
}

void ConstantBuffer::push(RenderManager& renderManager) {
	renderManager.getContext()->VSSetConstantBuffers(0, 1, buffer.GetAddressOf());
}

HRESULT ConstantBuffer::update(RenderManager& renderManager, ConstantBufferData* data) {
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	//map is better then updatesubresource when dealing with constant buffers
	HRESULT result = renderManager.getContext()->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	if (FAILED(result)) {
		MessageBoxW(NULL, L"Failed to map constant buffer", L"Error", MB_ICONERROR);
		throw RenderException(result);
	}

	CopyMemory(mappedResource.pData, data, sizeof(ConstantBufferData));
	renderManager.getContext()->Unmap(buffer.Get(), 0);
	return 0;
}
