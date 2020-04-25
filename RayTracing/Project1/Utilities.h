#ifndef UTILITIES_H
#define UTILITIES_H

// Headers comuns
#include "glm/glm.hpp"
#include "glm\gtx\norm.hpp"
#include <memory>
#include <vector>
#include <functional>
#include <random>


using std::shared_ptr;
using std::make_shared;

// Constantes

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

// Utilidades

inline float random_float() {
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    static std::function<float()> rand_generator = std::bind(distribution, generator);
    return rand_generator();
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

inline float ffmin(double a, double b) { return a <= b ? a : b; }
inline float ffmax(double a, double b) { return a >= b ? a : b; }

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline glm::vec3 scale_color(glm::vec3 vector, int samples) {
    float scale = 1.f / samples;
    float r = scale * vector.x;
    float g = scale * vector.y;
    float b = scale * vector.z;

    return glm::vec3(r, g, b);

}

#endif