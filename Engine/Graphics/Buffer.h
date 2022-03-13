#pragma once

#include <directxmath.h>
#include <wrl.h>
#include "../Utils.h"

class RenderManager;

class Buffer {
protected:
	const uint size;
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer = nullptr;
public:
	Buffer(uint size);
	virtual HRESULT init(ID3D11Device* device) = 0;
	virtual void push(RenderManager& renderManager) = 0;
	uint getSize();
};

