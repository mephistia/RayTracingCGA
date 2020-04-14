#include <iostream>
#include <fstream>
#include "HitableList.h"
#include "Sphere.h"
#include <cfloat>

// lerp cores
glm::vec3 color(const Ray &r, Hitable *world) {

	// guardar onde bateu
	hit_record rec;

	// verificar se bateu
	if (world->hit(r, 0.0f, FLT_MAX, rec)) {
		return 0.5f * glm::vec3(rec.normal.x + 1.0f, rec.normal.y + 1.0f, rec.normal.z + 1.0f);
	}

	// ou desenhar o fundo
	else {
		glm::vec3 unit_direction = glm::normalize(r.direction());
		float t = 0.5f * (unit_direction.y + 1.0f);
		// cores min e max (alaranjado e azul escuro)
		return (1.0f - t) * glm::vec3(0.6f, 0.4f, 0.3f) + t * glm::vec3(0.1f, 0.0f, 0.3f);

	}
	
}

int main() {

	// tamanho 2:1
	int nx = 600;
	int ny = 300;

	// criar arquivo
	std::ofstream img ("testImg.ppm");

	// escrever no arquivo
	if (img.is_open()) {
		img << "P3\n" << nx << " " << ny << "\n255\n";

		// vetores
		glm::vec3 llc(-2.0f, -1.0f, -1.0f);
		glm::vec3 horizontal(4.0f, 0.0f, 0.0f);
		glm::vec3 vertical(0.0f, 2.0f, 0.0f);
		glm::vec3 origin(0.0f, 0.0f, 0.0f);

		// criar objetos "atingíveis"
		Hitable *list[2];
		list[0] = new Sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
		list[1] = new Sphere(glm::vec3(0.0f, -100.5f, -1.0f), 100);

		// colocar os objetos na lista do mundo
		Hitable *world = new HitableList(list, 2);
		
		for (int j = ny - 1; j >= 0; j--) {
			for (int i = 0; i < nx; i++) {
		
				float u = float(i) / float(nx);
				float v = float(j) / float(ny);
				
				// raio sai da origem e vai na direção:
				Ray r(origin, llc + u * horizontal + v * vertical);

				glm::vec3 p = r.point_at_parameter(2.0f);
				glm::vec3 col = color(r, world);
				
				int ir = int(255.99 * col.r);
				int ig = int(255.99 * col.g);
				int ib = int(255.99 * col.b);

				img << ir << " " << ig << " " << ib << "\n";
			}
		}
	}

	return 0;
}