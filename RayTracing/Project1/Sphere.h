#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"

// esfera é um tipo de item detectável
class Sphere : public Hittable {
public:
    Sphere() {}
    Sphere(glm::vec3 cen, float r) : center(cen), radius(r) {};

    virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;

public:
    glm::vec3 center;
    float radius;
};

// verificar se bateu em uma esfera (direto, borda ou fora)
bool Sphere::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {

    glm::vec3 oc = r.origin() - center;
    float a = glm::length2(r.direction());
    float half_b = dot(oc, r.direction());
    float c = glm::length2(oc) - radius * radius;
    float discriminant = half_b * half_b - a * c;

    if (discriminant > 0) {
        float root = sqrt(discriminant);
        float temp = (-half_b - root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            glm::vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            return true;
        }
        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            glm::vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            return true;
        }
    }
    return false;
}


#endif