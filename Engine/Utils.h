#pragma once
#include <d3d.h>
#include <d3d11.h>
#include <limits>
#include <sstream>

typedef unsigned int uint;
typedef unsigned int uchar;

class RenderException : public std::exception {
public:
	const HRESULT errorCode;
	RenderException(HRESULT errorCode): errorCode(errorCode) {}
};

class Utils {
public:
	inline static void checkValid(HRESULT result) {
		if (FAILED(result)) {
			throw RenderException(result);
		}
	}

	float coerceInRange(float number, float min, float max) {
		if(number > max) {
			number = max;
		}

		if(number < min) {
			number = min;
		}

		return number;
	}
};