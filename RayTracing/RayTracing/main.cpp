#include <iostream>
#include <fstream>
#include <glm\glm.hpp>

int main() {

	// tamanho
	int nx = 400;
	int ny = 300;

	// criar arquivo
	std::ofstream img ("testImg.ppm");

	// escrever no arquivo
	if (img.is_open()) {
		img << "P3\n" << nx << " " << ny << "\n255\n";

		for (int j = ny - 1; j >= 0; j--) {
			for (int i = 0; i < nx; i++) {
				// versão com floats
				//float r = float(i) / float(nx);
				//float g = float(j) / float(ny);
				//float b = 0.2;

				//int ir = int(255.99 * r);
				//int ig = int(255.99 * g);
				//int ib = int(255.99 * b);

				// versão com vec3
				glm::vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
				
				int ir = int(255.99 * col.r);
				int ig = int(255.99 * col.g);
				int ib = int(255.99 * col.b);

				img << ir << " " << ig << " " << ib << "\n";
			}
		}
	}

	return 0;
}