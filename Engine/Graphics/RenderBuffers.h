#pragma once

#include "RenderType.h"
#include "VertexBuffer.h"
#include <vector>
#include <utility>

class RenderBuffers {
	std::vector<std::pair<RenderType&, VertexBuffer*>> buffers;

public:
	RenderBuffers() {
		RenderType rt(L"../Shaders/MyVeryFirstShader.hlsl",
					  VertexFormat(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST).add({"Position", DXGI_FORMAT_R32G32B32_FLOAT}));
		buffers.push_back(std::pair<RenderType&, VertexBuffer*>(rt, nullptr));
	}

	void init() {
		for (auto it = buffers.begin(); it != buffers.end(); ++it) {
			//it->first.init(/);
		}
	}
};