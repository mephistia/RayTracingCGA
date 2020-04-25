#pragma once
#include "Material.h"

glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n) {
	return v - 2 * dot(v, n) * n;
}

class Metal : public Material {
public:
	Metal(const glm::vec3& a) : albedo(a) {}

	virtual bool scatter(
		const Ray& r_in, const hit_record& rec, glm::vec3& attenuation, Ray& scattered
	) const {
		glm::vec3 reflected = reflect(glm::normalize(r_in.direction()), rec.normal);
		scattered = Ray(rec.p, reflected);
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}


	glm::vec3 albedo;

};
