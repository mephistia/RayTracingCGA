
#ifndef READINPUT_H
#define READINPUT_H

#include "Utilities.h"
#include "Camera.h"
#include "Metal.h"
#include "Lambertian.h"
#include "Dielectric.h"
#include "Sphere.h"
#include "HittableList.h"

class ReadInput
{
public:

	ReadInput() {}
	~ReadInput() {}

	ReadInput(std::string filename) {
		// abrir arquivo
		inputFile = std::ifstream(filename);

		if (inputFile.is_open()) {

			// Pré-requisito: as configs estão em formato correto

			// Largura e altura da imagem, antialiasing
			inputFile >> imgWidth >> imgHeight >> antialiasing;
			std::cerr << imgWidth << " " << imgHeight << " " << antialiasing << "\n";

			// Calcular Aspect Ratio
			aspectRatio = float(imgWidth) / imgHeight;

			// vetor lookfrom
			char X[100], Y[100], Z[100];
			inputFile >> X >> Y >> Z;
			std::cerr << (float)atof(X) << " " << (float)atof(Y) << " " << (float)atof(Z) << "\n";
			lookfrom = glm::vec3((float)atof(X), (float)atof(Y), (float)atof(Z));

			// vetor lookat
			inputFile >> X >> Y >> Z;
			std::cerr << (float)atof(X) << " " << " " << (float)atof(Y) << " " << (float)atof(Z) << "\n";
			lookat = glm::vec3((float)atof(X), (float)atof(Y), (float)atof(Z));


			// outras configs da câmera
			char data[100];
			inputFile >> data;
			distFocus = (float)atof(data);
			inputFile >> data;
			aperture = (float)atof(data);
			inputFile >> data;
			fov = (float)atof(data);
			std::cerr << distFocus <<  " " << aperture << " " << fov << "\n";


			// É Ray Tracing? (0 ou 1)
			inputFile >> rayTracing;
			std::cerr << rayTracing << "\n";

			// para Ray Tracing, existe um valor de max depth no arquivo
			if (rayTracing)
				inputFile >> maxDepth;
	
			else
				maxDepth = 2;

			std::cerr << maxDepth << "\n";


			// Qtd de esferas para ler
			inputFile >> spheresCount;
			std::cerr << spheresCount << "\n";


			for (int i = 0; i < spheresCount; i++) {

				// posição da esfera, raio e material
				inputFile >> X >> Y >> Z;
				inputFile >> data;
				r = (float)atof(data);
				inputFile >> material;
				position = glm::vec3((float)atof(X), (float)atof(Y), (float)atof(Z));
				std::cerr << X << " " << Y << " " << Z << " " << r << " " << "\n";


				// se possuir albedo
				if (material != 'D') {
					inputFile >> X >> Y >> Z;
					albedo = glm::vec3((float)atof(X), (float)atof(Y), (float)atof(Z));
					std::cerr << X << " " << Y << " " << Z;

					// metal possui fuzz
					if (material == 'M') {
						inputFile >> data;
						fuzz = (float)atof(data);
						std::cerr << " " << fuzz << "\n";
						// adicionar Metal ao mundo
						world.add(make_shared<Sphere>(position, r, make_shared<Metal>(albedo, fuzz)));
						std::cerr << "Sphere " << i << " done!\n";

					}
					else {
						// adicionar Lambert ao mundo
						world.add(make_shared<Sphere>(position, r, make_shared<Lambertian>(albedo)));
						std::cerr << "Sphere " << i << " done!\n";
					}
				}
				else {
					inputFile >> data;
					ref = (float)atof(data);
					std::cerr << " " << ref << "\n";
					// se for Ray Casting, ignora o D
					if (!rayTracing) {
						material = 'L';
						albedo = glm::vec3(0.5f, 0.5f, 0.5f);
						world.add(make_shared<Sphere>(position, r, make_shared<Lambertian>(albedo)));
						std::cerr << "Sphere " << i << " done!\n";

					}
					else
						world.add(make_shared<Sphere>(position, r, make_shared<Dielectric>(ref)));
					std::cerr << "Sphere " << i << " done!\n";
				}
			}

			// Criar esferas lambert random?
			inputFile >> createRandomSpheres;
			std::cerr << createRandomSpheres << "\n";


			if (createRandomSpheres) {
				inputFile >> randomSpheres;
				std::cerr << randomSpheres << "\n";

				for (int i = 0; i < randomSpheres; i++) {
					glm::vec3 center;
					do {
						center = glm::vec3(random_float(-5,5), 0.2, random_float(-5,5));

					} while (!((center - glm::vec3(2.0, 0.2, 0)).length() > 1));

					albedo = randomVec() * randomVec();
					world.add(
						make_shared<Sphere>(center, 0.2, make_shared<Lambertian>(albedo)));
					std::cerr << "Random Sphere " << i << " done!\n";

				}
			}

			inputFile.close();
		}

		// Depois de ler o arquivo, world pode ser chamado
		std::cerr << "Done reading file.\n";
	}

	HittableList getWorld(){
		return world;
	}

	Camera getCam(){
		vup = glm::vec3(0.f, 1.f, 0.f);

		Camera cam(lookfrom, lookat, vup, fov, aspectRatio, aperture, distFocus);
		return cam;
	}

	int getWidth(){
		return imgWidth;
	}
	int getHeight(){
		return imgHeight;
	}
	int getMaxDepth(){
		return maxDepth;
	}
	int getSamples(){
		return antialiasing;
	}

private:
	int imgWidth, imgHeight, antialiasing, maxDepth, spheresCount, randomSpheres, fov, r;
	bool createRandomSpheres;
	bool rayTracing;
	float distFocus, aperture, aspectRatio, fuzz, ref;
	HittableList world;
	glm::vec3 lookfrom;
	glm::vec3 lookat;
	glm::vec3 vup;
	glm::vec3 position;
	glm::vec3 albedo;
	std::ifstream inputFile;
	char material;

};

#endif