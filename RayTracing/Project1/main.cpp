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
    HittableList world = input.getWorld();
    Camera cam = input.getCam();


    // Renderizar
    Renderer renderer;
    renderer.renderImg(imgWidth, imgHeight, samples, maxDepth, world, cam);

    // Aplicar filtro
    Filter filter;
    filter.readImg("scene.ppm");
    filter.applyEmboss();
    filter.applyBlur();
    filter.saveImg("sceneFiltered.ppm"); // Salva os dados do vetor em uma imagem

    return 0;
    
}