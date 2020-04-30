#include "ReadInput.h"

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
    return (1.f - t) * glm::vec3(1.f, 1.f, 1.f) + t * glm::vec3(0.7f, .9f, 1.f);
}

int main() {

    ReadInput input("imgdata.config");

    // Ler do arquivo
    const int image_width = input.getWidth();
    const int image_height = input.getHeight();
    const int samples_per_pixel = input.getSamples();
    const int max_depth = input.getMaxDepth();


    // criar arquivo
    std::ofstream img("result.ppm");

    // escrever no arquivo
    if (img.is_open()) {

        // padronização PPM
        img << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        // Ler o arquivo e retornar o HittableList
        HittableList world = input.getWorld();

        
        // Retornar a câmera do arquivo lido
        Camera cam = input.getCam();

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