#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

// definição da câmera
class Camera {
public:
    Camera() {
        lower_left_corner = glm::vec3(-2.f, -1.f, -1.f);
        horizontal = glm::vec3(4.f, 0.f, 0.f);
        vertical = glm::vec3(0.f, 2.f, 0.f);
        origin = glm::vec3(0.f, 0.f, 0.f);
    }

    Ray get_ray(float u, float v) {
        return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

public:
    glm::vec3 origin;
    glm::vec3 lower_left_corner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
};
#endif