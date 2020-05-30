#pragma once

#include "rtweekend.hpp"

class CCamera
{
    public:
        CCamera()
        {
            const auto aspectRatio = 16.0 / 9.0;
            const auto viewportHeight = 2.0;
            const auto viewportWidth = aspectRatio * viewportHeight;
            const auto focalLength = 1.0;

            origin = point3(0, 0, 0);
            horizontal = vec3(viewportWidth, 0.0, 0.0);
            vertical = vec3(0.0, viewportHeight, 0.0);
            lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);
        }

        ray getRay(const double u, const double v) const
        {
            return ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
        }

    private:
        point3 origin;
        point3 lowerLeftCorner;
        vec3 horizontal;
        vec3 vertical;
};
