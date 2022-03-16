#pragma once
#include <vector>
#include <d3d11.h>
#include <iostream>
#include "../Utils.h"

struct VertexFormatElement {
	const LPCSTR semanticName;
	const DXGI_FORMAT format;
};

//Vertices are counterclock-wise
class VertexFormat {
private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> elements;
	const D3D_PRIMITIVE_TOPOLOGY topology;
public:
	VertexFormat(VertexFormat&& cfg) = default;
	VertexFormat(VertexFormat& cfg) = default;

	VertexFormat(D3D_PRIMITIVE_TOPOLOGY topology): topology(topology) {
	}

	VertexFormat& add(const VertexFormatElement& format) {
		D3D11_INPUT_ELEMENT_DESC desc = {
				format.semanticName,
				0,
				format.format,
				0,
				D3D11_APPEND_ALIGNED_ELEMENT,
				D3D11_INPUT_PER_VERTEX_DATA,
				0
		};

		elements.push_back(desc);

		return *this;
	}

	const D3D11_INPUT_ELEMENT_DESC& getFront() const {
		return elements.front();
	}

	const uint getSize() const {
		return elements.size();
	}

	D3D_PRIMITIVE_TOPOLOGY getTopology() {
		return topology;
	}
};
