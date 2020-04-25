#include <iostream>
#include <fstream>
#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"
#include "Metal.h"
#include "Lambertian.h"
#include "Dielectric.h"


// definir cor do pixel
glm::vec3 ray_color(const Ray& r, const Hittable& world, int depth) {

    hit_record rec;

    if (depth <= 0)
        return glm::vec3(0.f, 0.f, 0.f);

    if (world.hit(r, 0.001f, infinity, rec)) {
        Ray scattered;
        glm::vec3 attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return glm::vec3(0, 0, 0);
    }

    glm::vec3 unit_direction = glm::normalize(r.direction());
    float t = .5f * (unit_direction.y + 1.f);
    return (1.f - t) * glm::vec3(1.f, 1.f, 1.f) + t * glm::vec3(.5f, .7f, 1.f);
}

int main() {
    const int image_width = 400;
    const int image_height = 200;
    const int samples_per_pixel = 100;
    const int max_depth = 50;
    const float aspect_ratio = float(image_width) / image_height;




    // criar arquivo
    std::ofstream img("result.ppm");

    // escrever no arquivo
    if (img.is_open()) {

        // padronização PPM
        img << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        HittableList world;

        glm::vec3 lookfrom(13.f, 2.f, 3.f);
        glm::vec3 lookat(0.f, 0.f, 0.f);
        glm::vec3 vup(0.f, 1.f, 0.f);


        world.add(make_shared<Sphere>(
            glm::vec3(0.f, 0.f, -1.f), 0.5f, make_shared<Lambertian>(glm::vec3(.7f, .3f, .3f))));

        world.add(make_shared<Sphere>(
            glm::vec3(0.f, -100.5f, -1.f), 100.f, make_shared<Lambertian>(glm::vec3(.8f, .8f, 0.f))));

        world.add(make_shared<Sphere>(glm::vec3(1.f, 0.f, -1.f), 0.5f, make_shared<Metal>(glm::vec3(0.8f, 0.6f, 0.2f),0.4)));
        world.add(make_shared<Sphere>(glm::vec3(-1.f, 0.f, -1.f), 0.5f, make_shared<Dielectric>(1.5f)));
        world.add(make_shared<Sphere>(glm::vec3(-1.f, 0.f, -1.f), -0.45f, make_shared<Dielectric>(1.5f)));

        Camera cam(glm::vec3(-2.f,2.f,1.f), glm::vec3(0.f,0.f,-1.f),vup, 30, aspect_ratio);

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
                    color += ray_color(ray, world, max_depth);
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