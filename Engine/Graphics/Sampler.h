#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "Utils.h"

class RenderManager;

class Sampler {
public:
	Sampler(D3D11_FILTER filter, uint maxAnisotropy);

	HRESULT init(RenderManager& renderManager);
	void push(RenderManager& renderer);

private:
	D3D11_FILTER filter;
	uint maxAnisotropy;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
}; 

