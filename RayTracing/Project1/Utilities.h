#ifndef UTILITIES_H
#define UTILITIES_H

// Headers comuns
#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"
#include <memory>
#include <vector>
#include <functional>
#include <random>
#include <string>
#include <iostream>
#include <fstream>


using std::shared_ptr;
using std::make_shared;

// Constantes

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

// Utilidades

inline float random_float() {
    std::random_device rd;
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator(rd());
    static std::function<float()> rand_generator = std::bind(distribution, generator);
    return rand_generator();
}

inline float random_float(float min, float max) {
    return min + (max - min) * random_float();
}

//glm::vec3 randomInUnitSphere() {
//	glm::vec3 p;
//	do {
//		p = 2.0f * glm::vec3((std::rand() / (RAND_MAX + 1.0f)), (rand() / (RAND_MAX + 1.0f)), (rand() / (RAND_MAX + 1.0f))) - glm::vec3(1.0f, 1.0f, 1.0f);
//	} while (glm::length2(p) >= 1.0f);
//	return p;
//}

inline float degrees_to_radians(double degrees) {
	return degrees * pi / 180;
}

inline float ffmin(float a, float b) { return a <= b ? a : b; }
inline float ffmax(float a, float b) { return a >= b ? a : b; }

inline float clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline glm::vec3 scale_color(glm::vec3 vector, int samples) {
    float scale = 1.f / samples;
    float r = sqrt(scale * vector.x);
    float g = sqrt(scale * vector.y);
    float b = sqrt(scale * vector.z);

    return glm::vec3(r, g, b);

}

inline static glm::vec3 randomVec() {
    return glm::vec3(random_float(), random_float(), random_float());
}

inline static glm::vec3 randomVec(float min, float max) {
    return glm::vec3(random_float(min, max), random_float(min, max), random_float(min, max));
}

glm::vec3 random_in_unit_sphere() {
    while (true) {
        glm::vec3 p = randomVec(-1, 1);
        if (glm::length2(p) >= 1) continue;
        return p;
    }
}

glm::vec3 random_unit_vector() {
    auto a = random_float(0, 2 * pi);
    auto z = random_float(-1, 1);
    auto r = sqrt(1 - z * z);
    return glm::vec3(r * cos(a), r * sin(a), z);
}

glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n) {
    return v - 2 * dot(v, n) * n;
}

glm::vec3 refract(const glm::vec3& uv, const glm::vec3& n, float etai_over_etat) {
    auto cos_theta = dot(-uv, n);
    glm::vec3 r_out_parallel = etai_over_etat * (uv + cos_theta * n);
    glm::vec3 r_out_perp = -sqrt(1.0f - glm::length2(r_out_parallel)) * n;
    return r_out_parallel + r_out_perp;
}

float schlick(float cosine, float ref_idx) {
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

glm::vec3 random_in_unit_disk() {
    while (true) {
        auto p = glm::vec3(random_float(-1.f, 1.f), random_float(-1.f, 1.f), 0);
        if (glm::length2(p) >= 1) continue;
        return p;
    }
}

#endif