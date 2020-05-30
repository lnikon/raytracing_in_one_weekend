#pragma once

#include "ray.hpp"
#include "hittable.hpp"

class CMaterial
{
    public:
        virtual bool scatter(const ray& rin, const SHitRecord& rec, color& attenuation, ray& scattered) const = 0;
        virtual ~CMaterial() {}
};

class CLambertian : public CMaterial
{
    public:
        CLambertian(const color& a) : albedo(a) { }

        bool scatter(const ray& rin, const SHitRecord& rec, color& attenuation, ray& scattered) const override
        {
            vec3 scatterDirection = rec.normal + random_unit_vector();
            scattered = ray(rec.p, scatterDirection);
            attenuation = albedo;
            return true;
        }

    public:
        color albedo;
};


class CMetal : public CMaterial {

    public:
        CMetal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) { }
        bool scatter(const ray& r_in, const SHitRecord& rec, color& attenuation, ray& scattered) const override
        {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

    public:
        color albedo;
        double fuzz;
};

class CDielectric : public CMaterial
{
    public:
        CDielectric(double ri) : refIdx(ri) { }

        bool scatter(const ray& r_in, const SHitRecord& rec, color& attenuation, ray& scattered) const override
        {
            attenuation = color(1.0, 1.0, 1.0);
            double etai_over_etat;
            if (rec.frontFace)
            {
                etai_over_etat = 1.0 / refIdx;
            }
            else
            {
                etai_over_etat = refIdx;
            }

            vec3 unitDirection = unit_vector(r_in.direction());
            double cosTheta = fmin(dot(-unitDirection, rec.normal), 1.0);
            double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
            if (etai_over_etat * sinTheta > 1.0) // only reflects
            {
                vec3 refracted = refract(unitDirection, rec.normal, etai_over_etat);
                scattered = ray(rec.p, refracted);
                return true;
            }

            vec3 refracted = refract(unitDirection, rec.normal, etai_over_etat);
            scattered = ray(rec.p, refracted);
            return true;
        }

    public:
        double refIdx;
};
