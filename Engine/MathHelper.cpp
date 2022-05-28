#include "MathHelper.h"
#include <cmath>

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
