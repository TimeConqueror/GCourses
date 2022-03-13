#pragma once

#include "Buffer.h"
#include "ConstantBufferTypes.h"

class ConstantBuffer: public Buffer {
public:
	ConstantBuffer();
	virtual HRESULT init(ID3D11Device* device) override;
	virtual void push(RenderManager& renderManager) override;

	HRESULT update(RenderManager& renderManager, ConstantBufferData* data);
};

