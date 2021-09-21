// Umbra2D headers
#define STB_IMAGE_IMPLEMENTATION

#include "Umbra2D.h"

Umbra2D::Umbra2DEngine* umbra;

int main() {
    // start collecting mem allocations info
    MemPlumber::start();

    umbra = new Umbra2D::Umbra2DEngine();
    umbra->run();
    delete umbra;

    // run memory leak test in verbose mode
    size_t memLeakCount;
    uint64_t memLeakSize;
    MemPlumber::memLeakCheck(memLeakCount, memLeakSize, true);

    // print memory leak results
    if (memLeakCount)
        printf("Number of leaked objects: %d\nTotal amount of memory leaked: %d[bytes]\n", (int)memLeakCount, (int)memLeakSize);
    else
        printf("G f*ckin' G! There are no leaks to be seen");
    return 0;
}
