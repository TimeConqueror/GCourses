#pragma once
#include <SimpleMath.h>

struct Light
{
	DirectX::SimpleMath::Vector3 viewerPos;
	float dummy1 = -1;
	DirectX::SimpleMath::Vector3 direction;
	float dummy2 = -1;
	DirectX::SimpleMath::Vector3 color;
	float dummy3 = -1;

	Light(const DirectX::SimpleMath::Vector3& viewerPos, const DirectX::SimpleMath::Vector3& direction,
		const DirectX::SimpleMath::Vector3& color)
		: viewerPos(viewerPos),
		  direction(direction),
		  color(color) {
	}
};

