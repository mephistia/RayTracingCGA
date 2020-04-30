#ifndef RENDERER_H
#define RENDERER_H

#include "ReadInput.h"

class Renderer {
public:
	Renderer() {}
	~Renderer() {}

	void renderImg(
		const int imgWidth, const int imgHeight,
		const int samples, const int maxDepth, HittableList world, Camera cam) 
	{

        // criar arquivo de saída
        std::ofstream img("scene.ppm");


        if (img.is_open()) {

            // padronização PPM
            img << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";


            for (int j = imgHeight - 1; j >= 0; --j) {

                std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;


                for (int i = 0; i < imgWidth; ++i) {

                    glm::vec3 color(0.f, 0.f, 0.f);

                    for (int s = 0; s < samples; ++s) {
                        // antialiasing
                        auto u = (i + random_float()) / imgWidth;
                        auto v = (j + random_float()) / imgHeight;
                        // cores
                        Ray ray = cam.get_ray(u, v);
                        color += ray_cast(ray, world, maxDepth);
                    }

                    color = scale_color(color, samples);

                    // normalizar as cores p/ 0-255
                    int ir = int(256 * clamp(color.r, 0.f, .999f));
                    int ig = int(256 * clamp(color.g, 0.f, .999f));
                    int ib = int(256 * clamp(color.b, 0.f, .999f));

                    img << ir << ' ' << ig << ' ' << ib << '\n';
                }
            }
            std::cerr << "\nDone.\n";
            img.close();
        }

	}

    // Rodar o ray cast para o pixel
	glm::vec3 ray_cast(const Ray& r, const Hittable& world, int depth) {

        hit_record rec;

        if (depth <= 0)
            return glm::vec3(0.f, 0.f, 0.f);

        if (world.hit(r, 0.001f, infinity, rec)) {
            Ray scattered;
            glm::vec3 attenuation;
            if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_cast(scattered, world, depth - 1);
            return glm::vec3(0, 0, 0);
        }

        glm::vec3 unit_direction = glm::normalize(r.direction());
        float t = .5f * (unit_direction.y + 1.f);
        return (1.f - t) * glm::vec3(1.f, 1.f, 1.f) + t * glm::vec3(0.7f, .8f, 1.f);
	}

};


#endif
