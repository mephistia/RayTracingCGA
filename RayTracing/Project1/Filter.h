#ifndef FILTER_H
#define FILTER_H

#include "Utilities.h"

class Filter {
public:
	Filter() {}
	~Filter() {}

	void applyEmboss() {
		// Cria o filtro
		const int fh = 3, fw = 3;
		float filter[fh][fw] = 
		{
			{-1, -1,  0},
			{-1,  0,  1},
			{ 0,  1,  1}
		};

		float bias = 128.0;

		applyFilter(filter, bias);
	}

	void applyBlur() {

		// Cria o filtro
		const int fh = 5, fw = 5;
		float filter[fh][fw] =
		{	
			{1.0 / 256.0, 4.0 / 256.0, 6.0 / 256.0, 4.0 / 256.0, 1.0 / 256.0},
			{4.0 / 256.0, 16.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0, 4.0 / 256.0},
			{6.0 / 256.0, 24.0 / 256.0, 36.0 / 256.0, 24.0 / 256.0, 6.0 / 256.0},
			{4.0 / 256.0, 16.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0, 4.0 / 256.0},
			{1.0 / 256.0, 4.0 / 256.0, 6.0 / 256.0, 4.0 / 256.0, 1.0 / 256.0} 
		};

		applyFilter(filter,0.0);
	}

	// Filtro 5x5
	void applyFilter(float filter[5][5], float bias) {

		int fh = 5, fw = 5;

		// Vetor de resultado
		result.resize(imgHeight);

		for (int y = imgHeight - 1; y >= 0; --y) {
			result[y].resize(imgWidth);
			std::cerr << "\rScanlines remaining (Applying Filter): " << y << ' ' << std::flush;
			for (int x = 0; x < imgWidth; ++x) {

				// RGB finais
				float R = 0.0, G = 0.0, B = 0.0;
				glm::vec3 pixel(0);

				// multiplicar o filtro pelo pixel
				for (int a = 0; a < fw; a++) {
					for (int b = 0; b < fh; b++) {
						int xn = x + a;
						int yn = y + b;
						if (xn >= 0 && yn >= 0 &&
							xn < imgWidth && yn < imgHeight)
							pixel = image[yn][xn];

						R += pixel.r * filter[a][b];
						G += pixel.g * filter[a][b];
						B += pixel.b * filter[a][b];
					}
				}
				result[y][x].r = R + bias;
				result[y][x].g = G + bias;
				result[y][x].b = B + bias;

				//teste (motion blur)
				//image[y][x] = result[y][x];
				
			}
		}

		// Colocar o resultado no vetor de entrada
		// caso aplique mais de um filtro
		for (int y = imgHeight - 1; y >= 0; --y)
			for (int x = 0; x < imgWidth; ++x) {
				image[y][x] = result[y][x];
			}

		std::cerr << "\nDone.\n";

	}

	// Filtro 3x3
	void applyFilter(float filter[3][3], float bias) {
		int fh = 3, fw = 3;


		// Vetor de resultado
		result.resize(imgHeight);

		for (int y = imgHeight - 1; y >= 0; --y) {
			result[y].resize(imgWidth);
			std::cerr << "\rScanlines remaining (Applying Filter): " << y << ' ' << std::flush;
			for (int x = 0; x < imgWidth; ++x) {
				// Se não existir vetor ainda
				if (!result[y][x].r) {
					result[y][x] = glm::vec3(0);
				}
				// RGB finais
				float R = 0.0, G = 0.0, B = 0.0;
				glm::vec3 pixel(0);
				// multiplicar o pixel pelo filtro
				for (int a = 0; a < fw; a++) {
					for (int b = 0; b < fh; b++) {
						int xn = x + a;
						int yn = y + b;
						if (xn >= 0 && yn >= 0 &&
							xn < imgWidth && yn < imgHeight)
							pixel = image[yn][xn];

						R += pixel.r * filter[a][b];
						G += pixel.g * filter[a][b];
						B += pixel.b * filter[a][b];
					}
				}
				result[y][x].r = R + bias;
				result[y][x].g = G + bias;
				result[y][x].b = B + bias;
			}
		}

		// Colocar o resultado na imagem de entrada
		// caso aplique mais de um filtro
		for (int y = imgHeight - 1; y >= 0; --y)
			for (int x = 0; x < imgWidth; ++x) {
				image[y][x] = result[y][x];
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

			for (int j = imgHeight - 1; j >= 0; --j) {
				for (int i = 0; i < imgWidth; ++i) {
					output << result[j][i].r << ' ' << result[j][i].g << ' ' << result[j][i].b << '\n';

				}
			}


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

			image.resize(imgHeight);
			
			for (int j = imgHeight - 1; j >= 0; --j) {
				image[j].resize(imgWidth);

				for (int i = 0; i < imgWidth; ++i) {
					input >> pixel.r >> pixel.g >> pixel.b;
					image[j][i] = pixel;
				}
			}

			std::cerr << "\nDone.\n";

			input.close();
		}
	}

private:
	std::ifstream input;
	std::ofstream output;
	std::vector<std::vector<glm::vec3>> image;
	std::vector<std::vector<glm::vec3>> result;
	int imgWidth, imgHeight;

};

#endif