#pragma once
#include "Material.h"
#include "RandomPoint.h"

class Lambertian : public Material {
public:
	Lambertian(const glm::vec3& a) : albedo(a) { }

	virtual bool scatter(
		const Ray& r_in, const hit_record& rec, glm::vec3& attenuation, Ray& scattered
	) const {
		glm::vec3 scatter_dir = rec.normal + randomInUnitSphere();
		scattered = Ray(rec.p, scatter_dir);
		attenuation = albedo;
		return true;
	}

	glm::vec3 albedo;
};