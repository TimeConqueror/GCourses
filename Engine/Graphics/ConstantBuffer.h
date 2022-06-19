#pragma once

#include "Buffer.h"

template<typename DATA>
class ConstantBuffer: public Buffer {
public:
	ConstantBuffer();
	virtual HRESULT init(ID3D11Device* device) override;
	void pushForVertexShader(RenderManager& renderManager, uint slot = 0);
	void pushForPixelShader(RenderManager& renderManager, uint slot = 0);

	HRESULT update(RenderManager& renderManager, DATA* data);
};

