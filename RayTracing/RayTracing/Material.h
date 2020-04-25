#pragma once
#include "Ray.h"
#include "Hitable.h"
#include "glm/glm.hpp"

class Material {
public:
	virtual bool scatter(const Ray& r_in, const hit_record & rec, glm::vec3& attenuation, Ray& scattered) const = 0;
};