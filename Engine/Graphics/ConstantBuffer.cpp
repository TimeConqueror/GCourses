#include "ConstantBuffer.h"
#include "RenderManager.h"
#include <iostream>
#include <SimpleMath.h>

#include "LightData.h"
#include "ShadowMap.h"
#include "Renderables/ModelBasedRenderable.h"

//constant buffer is only 16-byte aligned?
template<typename DATA>
ConstantBuffer<DATA>::ConstantBuffer() : Buffer(sizeof(DATA) + (16 - sizeof(DATA) % 16)) {
}

template<typename DATA>
HRESULT ConstantBuffer<DATA>::init(ID3D11Device* device) {
	D3D11_BUFFER_DESC desc = {};

	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.ByteWidth = size;
	return device->CreateBuffer(&desc, 0, buffer.GetAddressOf());

}

template<typename DATA>
void ConstantBuffer<DATA>::pushForVertexShader(RenderManager& renderManager, uint slot) {
	renderManager.getContext()->VSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
}

template<typename DATA>
void ConstantBuffer<DATA>::pushForPixelShader(RenderManager& renderManager, uint slot) {
	renderManager.getContext()->PSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
}

template<typename DATA>
HRESULT ConstantBuffer<DATA>::update(RenderManager& renderManager, DATA* data) {
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	//map is better then updatesubresource when dealing with constant buffers
	HRESULT result = renderManager.getContext()->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	if (FAILED(result)) {
		MessageBoxW(NULL, L"Failed to map constant buffer", L"Error", MB_ICONERROR);
		throw RenderException(result);
	}

	CopyMemory(mappedResource.pData, data, sizeof(DATA));
	renderManager.getContext()->Unmap(buffer.Get(), 0);
	return 0;
}

template class ConstantBuffer<DirectX::SimpleMath::Matrix>;
template class ConstantBuffer<LightData>;
template class ConstantBuffer<Material>;
template class ConstantBuffer<Transform>;
//template class ConstantBuffer<ShadowMapShaderTransform>;