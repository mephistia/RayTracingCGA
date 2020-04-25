
#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"

class Lambertian : public Material {
public:
    Lambertian(const glm::vec3& a) : albedo(a) {}

    virtual bool scatter(const Ray& r_in, const hit_record& rec, glm::vec3& attenuation, Ray& scattered)
        const {
        glm::vec3 scatter_direction = rec.normal + random_unit_vector();
        scattered = Ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

public:
    glm::vec3 albedo;
};
#endif