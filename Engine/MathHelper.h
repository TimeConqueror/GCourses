#pragma once

class Math
{
public:
    constexpr static double PI = 3.14159265358979323846;
    constexpr static float PI_F = static_cast<float>(PI);

    /**
     * the angle is reduced to an angle between -180 and +180 by mod, and a 360 check
     */
    static float wrapDegrees(float value);

    static float wrapRadians(float value);

    /**
     * the angle is reduced to an angle between -180 and +180 by mod, and a 360 check
     */
    static double wrapDegrees(double value);
};

