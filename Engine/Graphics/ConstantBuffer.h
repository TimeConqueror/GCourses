#pragma once

#include "Buffer.h"

template<typename DATA>
class ConstantBuffer: public Buffer {
public:
	ConstantBuffer();
	virtual HRESULT init(ID3D11Device* device) override;
	virtual void push(RenderManager& renderManager) override;
	void push(RenderManager& renderManager, uint slot);

	HRESULT update(RenderManager& renderManager, DATA* data);
};

