#ifndef METAL_H
#define METAL_H

#include "Material.h"

class Metal : public Material {
public:
    Metal(const glm::vec3& a, float f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(
        const Ray& r_in, const hit_record& rec, glm::vec3& attenuation, Ray& scattered
    ) const {
        glm::vec3 reflected = reflect(glm::normalize(r_in.direction()), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

public:
    glm::vec3 albedo;
    float fuzz;
};

#endif