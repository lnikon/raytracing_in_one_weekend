#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degreesToRadians(double degrees)
{
    return degrees * pi / 180;
}

inline double random_double()
{

    // std::random_device rd;
    // static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    // static std::mt19937 generator(rd());
    // return distribution(generator);
    
    double r = rand() / (RAND_MAX + 1.0);
    return r;
}

bool cmpdbl(const double a, const double b)
{
    return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
}

static bool isDefinitelyLessThan(double a, double b, double tolerance = std::numeric_limits<double>::epsilon())
{
    double diff = a - b;
    if (diff < tolerance) return true;
    if (diff < std::fmax(std::fabs(a), std::fabs(b)) * tolerance) return true;
    return false;
}

static bool isDefinitelyGreaterThan(double a, double b, double tolerance = std::numeric_limits<double>::epsilon())
{
    double diff = a - b;
    if (diff > tolerance) return true;
    if (diff > std::fmax(std::fabs(a), std::fabs(b)) * tolerance) return true;
    return false;
}

inline double random_double(double min, double max)
{
    return min + (max - min) * random_double();
}

inline double clamp(const double x, const double min, const double max)
{
    if (std::isless(x, min)) return min;
    if (std::isgreater(x, max)) return max;
    return x;
}
