#ifndef RAY_H
#define RAY_H

#include "Utilities.h"

// classe para Ray Casting
class Ray {
public:
    Ray() {}
    Ray(const glm::vec3& origin, const glm::vec3& direction): orig(origin), dir(direction){}

    // retornar origem e direção do raio
    glm::vec3 origin() const { return orig; }
    glm::vec3 direction() const { return dir; }

    // apontar para
    glm::vec3 at(float t) const {
        return orig + t * dir;
    }

public:
    glm::vec3 orig;
    glm::vec3 dir;
};

#endif