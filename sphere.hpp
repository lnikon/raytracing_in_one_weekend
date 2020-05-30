#pragma once

#include "hittable.hpp"
#include "vec3.hpp"

class CSphere : public CHittable
{
    public:
        CSphere() {}
        CSphere(point3 cen, double r, std::shared_ptr<CMaterial> pm) : center(cen), radius(r), pmat(pm) {}

        virtual bool hit(const ray& r, double tmin, double tmax, SHitRecord& rec) const
        {
            vec3 oc = r.origin() - center;
            auto a = r.direction().length_squared();
            auto half_b = dot(oc, r.direction());
            auto c = oc.length_squared() - radius * radius;
            auto discriminant = half_b * half_b - a * c;
            if (discriminant > 0)
            {
                auto root = sqrt(discriminant);
                auto temp  = (-half_b - root) / a;
                if (temp < tmax && temp > tmin)
                {
                    rec.t = temp;
                    rec.p = r.at(rec.t);
                    vec3 outwardNormal = (rec.p - center) / radius;
                    rec.setFaceNormal(r, outwardNormal);
                    rec.pmat = pmat;
                    return true;
                }
                temp = (-half_b + root) / a;
                if (temp < tmax && temp > tmin)
                {
                    rec.t = temp;
                    rec.p = r.at(rec.t);
                    vec3 outwardNormal = (rec.p - center) / radius;
                    rec.setFaceNormal(r, outwardNormal);
                    rec.pmat = pmat;
                    return true;
                }
            }
            return false;
        }

    public:
        point3 center;
        double radius;
        std::shared_ptr<CMaterial> pmat;
};
