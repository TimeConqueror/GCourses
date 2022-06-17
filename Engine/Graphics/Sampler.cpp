#include "Sampler.h"

#include "RenderManager.h"

Sampler::Sampler(D3D11_FILTER filter, uint maxAnisotropy)
	: filter(filter)
	, maxAnisotropy(maxAnisotropy)
	, samplerState(nullptr)
{}

HRESULT Sampler::init(RenderManager& renderManager) {
	D3D11_SAMPLER_DESC sampler_desc = {};
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.Filter = filter;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampler_desc.BorderColor[0] = 1.0f;
	sampler_desc.BorderColor[1] = 0.0f;
	sampler_desc.BorderColor[2] = 0.0f;
	sampler_desc.BorderColor[3] = 1.0f;
	sampler_desc.MaxLOD = INT_MAX;
	sampler_desc.MaxAnisotropy = maxAnisotropy;

	return renderManager.getDevice()->CreateSamplerState(&sampler_desc, &samplerState);
}

void Sampler::push(RenderManager& renderManager) {
	renderManager.getContext()->PSSetSamplers(0, 1, samplerState.GetAddressOf());
}