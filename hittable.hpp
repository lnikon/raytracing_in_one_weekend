#pragma once

#include "ray.hpp"

class CMaterial;
struct SHitRecord
{
    point3 p;
    vec3 normal;
    std::shared_ptr<CMaterial> pmat;
    double t;
    bool frontFace;

    inline void setFaceNormal(const ray& r, const vec3& outwardNormal)
    {
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class CHittable
{
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, SHitRecord& rec) const = 0;
        virtual ~CHittable() {}
};
