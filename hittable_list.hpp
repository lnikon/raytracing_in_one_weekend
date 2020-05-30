#pragma once

#include "hittable.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class CHittableList : public CHittable
{
    public:
        CHittableList() { }
        CHittableList(std::shared_ptr<CHittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(std::shared_ptr<CHittable> object) { objects.emplace_back(object); }

        bool hit(const ray& r, double tmin, double tmax, SHitRecord& rec) const override 
        {
            SHitRecord tempRec;
            bool hitAnything = false;
            auto closestSoFar = tmax;
            
            for (const auto& object : objects)
            {
                if (object->hit(r, tmin, closestSoFar, tempRec))
                {
                    hitAnything = true;
                    closestSoFar = tempRec.t;
                    rec = tempRec;
                }
            }

            return hitAnything;
        }

    public:
        std::vector<std::shared_ptr<CHittable>> objects;
};
