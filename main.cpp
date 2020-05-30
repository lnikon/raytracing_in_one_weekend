#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "rtweekend.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "material.hpp"

#include <iostream>

double hit_sphere(const point3& center, double radius, const ray& r)
{
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-half_b - sqrt(discriminant)) / (a);
    }
}

color ray_color(const ray& r, const CHittable& world, const int depth)
{
    SHitRecord rec;
    if (depth <= 0)
    {
        return color(0, 0, 0);
    }
    
    if (world.hit(r, 0.001, infinity, rec))
    {
        ray scattered;
        color attenuation;
        if (rec.pmat->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * ray_color(scattered, world, depth - 1);
        }

        point3 target = rec.p + rec.normal + random_in_hemisphere(rec.normal);
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
    }
    vec3 unitDirection = unit_vector(r.direction());
    auto t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    const auto aspect_ratio = 16.0 / 9.0;
    // const int image_width = 384;
    // const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int image_width = 1920;
    const int image_height = 1080;
    const int samples_per_pixel = 1;
    const int max_depth = 50;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    CCamera cam;

    CHittableList world;
    world.add(std::make_shared<CSphere>(point3(0, 0, -1), 0.5, 
                std::make_shared<CLambertian>(color(0.7, 0.3, 0.3))));

    world.add(std::make_shared<CSphere>(point3(0, -100.5, -1), 100, 
                std::make_shared<CLambertian>(color(0.8, 0.8, 0.0))));

    world.add(std::make_shared<CSphere>(point3(1, 0, -1), 0.5, 
                std::make_shared<CMetal>(color(.8, .6, .2), 0.1)));

    world.add(std::make_shared<CSphere>(point3(-1, 0, -1), 0.5, 
                std::make_shared<CDielectric>(1.9)));

    for (int j = image_height - 1; j >= 0; --j)
    {
        //std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.getRay(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    //std::cerr << "\nDone.\n";

    return 0;
}
