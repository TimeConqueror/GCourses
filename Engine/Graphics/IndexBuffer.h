#pragma once
#include "Buffer.h"

class IndexBuffer: public Buffer {
private:
	std::vector<uint> indices;

public:
	IndexBuffer(std::vector<uint> indices);
	virtual HRESULT init(ID3D11Device* device) override;
	virtual void push(RenderManager& renderManager) override;
};

