#include "Renderer.h"
#include "Filter.h"

int main() {
    // Abrir arquivo e criar esferas
    ReadInput input("imgdata.config");

    // Ler do arquivo
    const int imgWidth = input.getWidth();
    const int imgHeight = input.getHeight();
    const int samples = input.getSamples();
    const int maxDepth = input.getMaxDepth();


    // retornar o HittableList
    HittableList world = input.getWorld();

    // Retornar a câmera do arquivo lido
    Camera cam = input.getCam();

    // Renderizar
  /*  Renderer renderer;
    renderer.renderImg(imgWidth, imgHeight, samples, maxDepth, world, cam);*/

    // Aplicar filtro
    Filter filter;
    filter.applyBlur("scene.ppm"); // Lê os dados do arquivo e salva em um vetor

    /*filter.readImg("scene.ppm");*/     // teste
    filter.saveImg("sceneFiltered.ppm"); // Salva os dados do vetor em uma imagem

    return 0;
    
}