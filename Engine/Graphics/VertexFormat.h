#pragma once
#include <vector>
#include <d3d11.h>
#include <iostream>
#include "../Utils.h"

struct VertexFormatElement {
	const LPCSTR semanticName;
	const DXGI_FORMAT format;
};

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
		uint alignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		if (elements.size() > 1) {
			alignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;// bug with format size > 2?
		}

		D3D11_INPUT_ELEMENT_DESC desc = {
				format.semanticName,
				0,
				format.format,
				0,
				alignedByteOffset,
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
