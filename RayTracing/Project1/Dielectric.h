#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.h"

class Dielectric : public Material {
public:
    Dielectric(float ri) : ref_idx(ri) {}

    virtual bool scatter(
        const Ray& r_in, const hit_record& rec, glm::vec3& attenuation, Ray& scattered
    ) const {
        attenuation = glm::vec3(1.0f, 1.0f, 1.0f);

        double etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);

        glm::vec3 unit_direction = normalize(r_in.direction());

        double cos_theta = ffmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
        if (etai_over_etat * sin_theta > 1.0) {
            glm::vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = Ray(rec.p, reflected);
            return true;
        }

        double reflect_prob = schlick(cos_theta, etai_over_etat);
        if (random_float() < reflect_prob)
        {
            glm::vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = Ray(rec.p, reflected);
            return true;
        }

        glm::vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
        scattered = Ray(rec.p, refracted);
        return true;
    }

    double ref_idx;
};

#endif