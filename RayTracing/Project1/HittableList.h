#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include "Hittable.h"

// Lista de objetos atingidos
class HittableList : public Hittable {
public:
    HittableList() {}
    HittableList(shared_ptr<Hittable> object) { add(object); }

    // limpar a lista de objetos atingidos
    void clear() { objects.clear(); }

    // adicionar um item à lista de objetos aitngidos
    void add(shared_ptr<Hittable> object) { objects.push_back(object); }

    virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const;

public:
    std::vector<shared_ptr<Hittable>> objects; // vetor de objetos atingidos
};

bool HittableList::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif