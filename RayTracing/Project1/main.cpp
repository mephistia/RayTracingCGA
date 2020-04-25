#include <iostream>
#include <fstream>
#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"


// definir cor do pixel
glm::vec3 ray_color(const Ray& r, const Hittable& world) {

    hit_record rec;

    if (world.hit(r, 0, infinity, rec)) {
        return 0.5f * (rec.normal + glm::vec3(1.f, 1.f, 1.f));
    }

    glm::vec3 unit_direction = glm::normalize(r.direction());
    float t = .5f * (unit_direction.y + 1.f);
    return (1.f - t) * glm::vec3(1.f, 1.f, 1.f) + t * glm::vec3(.5f, .7f, 1.f);
}

int main() {
    const int image_width = 400;
    const int image_height = 200;
    const int samples_per_pixel = 100;


    // criar arquivo
    std::ofstream img("result.ppm");

    // escrever no arquivo
    if (img.is_open()) {

        // padronização PPM
        img << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        glm::vec3 lower_left_corner(-2.f, -1.f, -1.f);
        glm::vec3 horizontal(4.f, 0.f, 0.f);
        glm::vec3 vertical(0.f, 2.f, 0.f);
        glm::vec3 origin(0.f, 0.f, 0.f);

        HittableList world;
        world.add(make_shared<Sphere>(glm::vec3(0.f, 0.f, -1.f), 0.5f));
        world.add(make_shared<Sphere>(glm::vec3(0.f, -100.5f, -1.f), 100.f));

        Camera cam;

        for (int j = image_height - 1; j >= 0; --j) {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;


            for (int i = 0; i < image_width; ++i) {

                glm::vec3 color(0.f, 0.f, 0.f);

                for (int s = 0; s < samples_per_pixel; ++s) {
                    // antialiasing
                    auto u = (i + random_float()) / image_width;
                    auto v = (j + random_float()) / image_height;
                    // cores
                    Ray ray = cam.get_ray(u, v);
                    color += ray_color(ray, world);
                }



                //float r = float(i) / image_width;
                //float g = float(j) / image_height;
                //float b = 0.2f;

                color = scale_color(color, samples_per_pixel);

                int ir = int(256 * clamp(color.r, 0.f, .999f));
                int ig = int(256 * clamp(color.g, 0.f, .999f));
                int ib = int(256 * clamp(color.b, 0.f, .999f));

                img << ir << ' ' << ig << ' ' << ib << '\n';
            }
        }
        std::cerr << "\nDone.\n";
        img.close();
    }
    return 0;
    
}