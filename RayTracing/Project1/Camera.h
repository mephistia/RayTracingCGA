#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

// definição da câmera
class Camera {
public:
    Camera(
        glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup,
        double vfov, // top to bottom, in degrees
        double aspect) {
        origin = lookfrom;
        glm::vec3 u, v, w;

        float theta = degrees_to_radians(vfov);
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;

        w = glm::normalize(lookfrom - lookat);
        u = glm::normalize(cross(vup, w));
        v = cross(w, u);

        lower_left_corner = origin - half_width * u - half_height * v - w;

        horizontal = 2 * half_width * u;
        vertical = 2 * half_height * v;
    }

    
    Ray get_ray(float s, float t) {
        return Ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
    }

public:
    glm::vec3 origin;
    glm::vec3 lower_left_corner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
};
#endif