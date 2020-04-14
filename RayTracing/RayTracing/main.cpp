#include <iostream>
#include <fstream>
#include "Ray.h"

// lerp branco e azul (fundo)
glm::vec3 color(const Ray &r) {
	glm::vec3 unit_direction;
	glm::vec3 unit_vector(r.direction());
	unit_direction = unit_vector;
	
	float t = 0.5f * (unit_direction.y + 1.0f);
	// cores min e max (amarelado e azul escuro)
	return (1.0f - t) * glm::vec3(0.6f, 0.4f, 0.3f) + t * glm::vec3(0.1f, 0.0f, 0.3f);
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

		for (int j = ny - 1; j >= 0; j--) {
			for (int i = 0; i < nx; i++) {
				// vers�o com floats
				//float r = float(i) / float(nx);
				//float g = float(j) / float(ny);
				//float b = 0.2;

				//int ir = int(255.99 * r);
				//int ig = int(255.99 * g);
				//int ib = int(255.99 * b);

				// vers�o com vec3
				//glm::vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);

				// vers�o com raio
				float u = float(i) / float(nx);
				float v = float(j) / float(ny);
				
				// raio sai da origem e vai na dire��o:
				Ray r(origin, llc + u * horizontal + v * vertical);

				glm::vec3 col = color(r);

				
				int ir = int(255.99 * col.r);
				int ig = int(255.99 * col.g);
				int ib = int(255.99 * col.b);

				img << ir << " " << ig << " " << ib << "\n";
			}
		}
	}

	return 0;
}