#ifndef FILTER_H
#define FILTER_H

#include "Utilities.h"

class Filter {
public:
	Filter() {}
	~Filter() {}

	void applyBlur(std::string fileToLoad) {

		readImg(fileToLoad);

		// Cria o filtro
		const int filterWidth = 3, filterHeight = 3;

		float filter[filterHeight][filterWidth] =
		{
			{0, 0, 0},
			{0, 1, 0},
			{0, 0, 0}
		};

		float factor = 1.0;
		float bias = 0.0;

		// Vetor de resultado
		result.resize(image.size());

		float R = 0.0, G = 0.0, B = 0.0;

		// Para cada pixel da imagem

		for (int x = 0; x < imgWidth; x++) {
			std::cerr << "\rScanlines remaining (Applying Blur): " << imgWidth - x << ' ' << std::flush;

			for (int y = 0; y < imgHeight; y++) {

				// converter para float
				image[y * imgWidth + x].r /= 255.f;
				image[y * imgWidth + x].g /= 255.f;
				image[y * imgWidth + x].b /= 255.f;

				// multiplicar o pixel pelo filtro
				for (int filterY = 0; filterY < filterHeight; filterY++) {
					for (int filterX = 0; filterX < filterWidth; filterX++) {

						int imageX = (x - filterWidth / 2 + filterX + imgWidth) % imgWidth;
						int imageY = (y - filterHeight / 2 + filterY + imgHeight) % imgHeight;

						// Aplicar no RGB do pixel
						R += image[imageY * imgWidth + imageX].r * filter[filterY][filterX];
						G += image[imageY * imgWidth + imageX].g * filter[filterY][filterX];
						B += image[imageY * imgWidth + imageX].b * filter[filterY][filterX];
					}
				}

				// Truncar os valores p/ o vetor de resultado

				result[y * imgWidth + x].r = int(256 * clamp(int(factor * R + bias), 0.f, .999f));
				result[y * imgWidth + x].g = int(256 * clamp(int(factor * G + bias), 0.f, .999f));
				result[y * imgWidth + x].b = int(256 * clamp(int(factor * B + bias), 0.f, .999f));
			}
		}
		std::cerr << "\nDone.\n";
	}

	void saveImg(std::string fileToSave) {
		// cria arquivo de saída
		output = std::ofstream(fileToSave);

		// teste
		//result = image;

		if (output.is_open()) {
			std::cerr << "Writing image.\n";

			output << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";

			for (int y = 0; y < imgHeight; y++)
				for (int x = 0; x < imgWidth; x++) {
					output << result[y * imgWidth + x].r << ' ' << result[y * imgWidth + x].g << ' ' << result[y * imgWidth + x].b << '\n';
				}
			/*for (int i = 0; i < imgWidth * imgHeight; i++) {
				output << result[i].r << ' ' << result[i].g << ' ' << result[i].b << '\n';
			}*/

			std::cerr << "\nDone.\n";


			output.close();
		}

	}

	void readImg(std::string file) {
		// Lê a imagem renderizada
		input = std::ifstream(file);
		glm::vec3 pixel;


		if (input.is_open()) {
			std::cerr << "Reading image.\n";

			char data[100]; // buffer
			input >> data; // P3
			input >> imgWidth >> imgHeight;
			input >> data; // 255

			image.resize(imgWidth * imgHeight);


			for (int i = 0; i < imgWidth * imgHeight; i++) {
				input >> pixel.r >> pixel.g >> pixel.b;
				image[i] = pixel;
			}
			std::cerr << "\nDone.\n";

			input.close();
		}
	}

private:
	std::ifstream input;
	std::ofstream output;
	std::vector<glm::vec3> image;
	std::vector<glm::vec3> result;
	int imgWidth, imgHeight;

};

#endif