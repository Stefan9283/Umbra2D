// Umbra2D headers
#define STB_IMAGE_IMPLEMENTATION

#include "Common.h"
#include "Engines/Engine.h"

Umbra2D::Umbra2DEngine* umbra;

int main() {
    umbra = new Umbra2D::Umbra2DEngine();
    umbra->run();
    delete umbra;
    return 0;
}
