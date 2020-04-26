#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

// definição da câmera
class Camera {
public:
    Camera(
        glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup,
        float vfov, // top to bottom, in degrees
        float aspect,
        float aperture,
        float focus_dist
        ) {
        origin = lookfrom;
        lens_radius = aperture / 2;

        float theta = degrees_to_radians(vfov);
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;

        w = glm::normalize(lookfrom - lookat);
        u = glm::normalize(cross(vup, w));
        v = cross(w, u);

        lower_left_corner = origin
            - half_width * focus_dist * u
            - half_height * focus_dist * v
            - focus_dist * w;

        horizontal = 2 * half_width * focus_dist * u;
        vertical = 2 * half_height * focus_dist * v;
    }

    
    Ray get_ray(float s, float t) {
        glm::vec3 rd = lens_radius * random_in_unit_disk();
        glm::vec3 offset = u * rd.x + v * rd.y;

        return Ray(
            origin + offset,
            lower_left_corner + s * horizontal + t * vertical - origin - offset
        );
    }

public:
    glm::vec3 origin;
    glm::vec3 lower_left_corner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
    glm::vec3 u, v, w;
    float lens_radius;
};
#endif