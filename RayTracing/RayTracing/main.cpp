#include <iostream>
#include <fstream>

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
				float r = float(i) / float(nx);
				float g = float(j) / float(ny);
				float b = 0.3;

				int ir = int(255.99 * r);
				int ig = int(255.99 * g);
				int ib = int(255.99 * b);
				img << ir << " " << ig << " " << ib << "\n";
			}
		}
	}

	return 0;
}