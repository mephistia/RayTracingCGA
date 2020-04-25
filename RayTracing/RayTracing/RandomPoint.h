#pragma once
#include "glm/glm.hpp"
#include "glm\gtx\norm.hpp"

glm::vec3 randomInUnitSphere() {
	glm::vec3 p;
	do {
		p = 2.0f * glm::vec3((std::rand() / (RAND_MAX + 1.0f)), (rand() / (RAND_MAX + 1.0f)), (rand() / (RAND_MAX + 1.0f))) - glm::vec3(1.0f, 1.0f, 1.0f);
	} while (glm::length2(p) >= 1.0f);
	return p;
}
