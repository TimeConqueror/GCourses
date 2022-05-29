#include "MathHelper.h"

#include <chrono>
#include <cmath>
#include <d3dtypes.h>

float Math::wrapDegrees(float value) {
	float f = std::fmod(value, 360.0F);
	if (f >= 180.0F) {
		f -= 360.0F;
	}

	if (f < -180.0F) {
		f += 360.0F;
	}

	return f;
}

double Math::wrapDegrees(double value) {
	double f = std::fmod(value, 360.0);
	if (f >= 180.0) {
		f -= 360.0;
	}

	if (f < -180.0) {
		f += 360.0;
	}

	return f;
}

float Math::toDegrees(float radians) {
	return radians * 180.0F / PI_F;
}

float Math::toRadians(float degrees) {
	return degrees / 180.0F * PI_F;
}

DirectX::SimpleMath::Vector3 Math::toRadians(DirectX::SimpleMath::Vector3 degrees) {
	return degrees / 180.0F * PI_F;
}

long Math::currentMillis() {
	const std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		);

	return ms.count();
}

DirectX::SimpleMath::Color Math::color(int argb) {
	return DirectX::SimpleMath::Color(RGBA_GETRED(argb) / 255.0F, RGBA_GETGREEN(argb) / 255.0F, RGBA_GETBLUE(argb) / 255.0F, RGBA_GETALPHA(argb) / 255.0F);
}

float Math::wrapRadians(float value) {
	float f = std::fmod(value, 2 * PI_F);
	if (f >= PI_F) {
		f -= 2 * PI_F;
	}

	if (f < -PI_F) {
		f += 2 * PI_F;
	}

	return f;
}
