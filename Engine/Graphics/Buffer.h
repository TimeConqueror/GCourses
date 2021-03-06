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
	Buffer(Buffer&& other) = default;
	Buffer(uint size);
	virtual HRESULT init(ID3D11Device* device) = 0;
	uint getSize();
};

