#ifndef MATERIAL_H
#define MATERIAL_H

#include "Hittable.h"

class Material {
public:
    virtual bool scatter(const Ray& r_in, const hit_record& rec, glm::vec3& attenuation, Ray& scattered) const = 0;
};



#endif