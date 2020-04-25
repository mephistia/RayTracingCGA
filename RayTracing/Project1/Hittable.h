#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"
class Material;


// struct que guarda onde bateu
struct hit_record {
    glm::vec3 p;
    glm::vec3 normal;
    shared_ptr<Material> mat_ptr;
    float t;
    bool front_face;

    inline void set_face_normal(const Ray& r, const glm::vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};


// qualquer objeto que pode ser detectado
class Hittable {
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif