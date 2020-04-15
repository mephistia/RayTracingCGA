/*
-> Completar o tutorial Ray Tracing in a Weekend
-> Adaptar e separar conforme as classes do enunciado
-> Adicionar Ray Casting simples com modelo Phong (sem Ray Tracing)
-> Ler arquivo de config
*/


#include <iostream>
#include <fstream>
#include "HitableList.h"
#include "Sphere.h"
#include "Camera.h"
#include <cfloat>
#include <time.h>
#include "glm\gtx\norm.hpp"

// ponto random (Ray Tracing)
glm::vec3 randomInUnitSphere() {
	glm::vec3 p;
	do {
		p = 2.0f * glm::vec3((rand() / (RAND_MAX + 1.0f)), (rand() / (RAND_MAX + 1.0f)), (rand() / (RAND_MAX + 1.0f))) - glm::vec3(1.0f, 1.0f, 1.0f);
	} while (glm::length2(p) >= 1.0f);
	return p;
}

// lerp cores
glm::vec3 color(const Ray &r, Hitable *world) {

	// guardar onde bateu
	hit_record rec;

	// verificar se bateu (Ray Casting)
	/*if (world->hit(r, 0.0f, FLT_MAX, rec)) {
		return 0.5f * glm::vec3(rec.normal.x + 1.0f, rec.normal.y + 1.0f, rec.normal.z + 1.0f);
	}*/

	// verificar se bateu (Ray Tracing)
	if (world->hit(r, 0.01f, FLT_MAX, rec)) {
		glm::vec3 target = rec.p + rec.normal + randomInUnitSphere();
		return 0.5f * color(Ray(rec.p, target - rec.p), world);
	}

	// ou desenhar o fundo
	else {
		glm::vec3 unit_direction = glm::normalize(r.direction());
		float t = 0.5f * (unit_direction.y + 1.0f);
		// cores min e max (alaranjado e azul escuro)
		return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);

	}
	
}

int main() {
	srand(time(NULL));

	// tamanho 2:1
	int nx = 600;
	int ny = 300;

	// qtd anti-aliasing
	int ns = 10;

	// criar arquivo
	std::ofstream img ("testImg.ppm");

	// escrever no arquivo
	if (img.is_open()) {
		img << "P3\n" << nx << " " << ny << "\n255\n";

		// criar objetos "atingíveis"
		Hitable *list[2];
		list[0] = new Sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
		list[1] = new Sphere(glm::vec3(0.0f, -100.5f, -1.0f), 100);

		// colocar os objetos na lista do mundo
		Hitable *world = new HitableList(list, 2);

		Camera cam;
		
		for (int j = ny - 1; j >= 0; j--) {
			for (int i = 0; i < nx; i++) {
		
				glm::vec3 col(0.0f, 0.0f, 0.0f);

				// anti-aliasing
				for (int s = 0; s < ns; s++) {
					float u = float(i + (rand() / (RAND_MAX + 1.0f))) / float(nx);
					float v = float(j + (rand() / (RAND_MAX + 1.0f))) / float(ny);
					
					Ray r = cam.getRay(u, v);
					glm::vec3 p = r.point_at_parameter(2.0f);
					col += color(r, world);
				}
				
				col /= float(ns);
				
				// pegar raiz p/ ficar mais claro
				col = glm::vec3(sqrt(col.r), sqrt(col.g), sqrt(col.b));

				int ir = int(255.99 * col.r);
				int ig = int(255.99 * col.g);
				int ib = int(255.99 * col.b);

				img << ir << " " << ig << " " << ib << "\n";
			}
		}

		img.close();
	}

	return 0;
}