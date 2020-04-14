#ifndef CAMERAH
#define CAMERAH

#include "Ray.h"

class Camera {
public:
	Camera() {
		llc = glm::vec3(-2.0f, -1.0f, -1.0f);
		horizontal = glm::vec3(4.0f, 0.0f, 0.0f);
		vertical = glm::vec3(0.0f, 2.0f, 0.0f);
		origin = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	Ray getRay(float u, float v) { return Ray(origin, llc + u * horizontal + v * vertical - origin); }

	glm::vec3 origin, llc, horizontal, vertical;
};

#endif