// Umbra2D headers
#define STB_IMAGE_IMPLEMENTATION

#include <lapi.h>
#include "Umbra2D.h"

Umbra2D::Umbra2DEngine* umbra;

int main() {
//    // start collecting mem allocations info
//    MemPlumber::start();
//
//    umbra = new Umbra2D::Umbra2DEngine();
//    umbra->run();
//    delete umbra;
//
//    // run memory leak test in verbose mode
//    size_t memLeakCount;
//    uint64_t memLeakSize;
//    MemPlumber::memLeakCheck(memLeakCount, memLeakSize, true);
//
//    // print memory leak results
//    if (memLeakCount)
//        printf("Number of leaked objects: %d\nTotal amount of memory leaked: %d[bytes]\n", (int)memLeakCount, (int)memLeakSize);
//    else
//        printf("G f*ckin' G! There are no leaks to be seen");

//    Umbra2D::Script s;
//    s.readFromFile("script.chai");
//    s.evaluate();

//    chaiscript::ChaiScript chai; // initializes ChaiScript, adding the standard ChaiScript types (map, string, ...)
//    typedef std::vector<int> data_list;
//    data_list my_list{ 0, 1, 2 };
//    chaiscript::Module m;
//    chai.add(chaiscript::bootstrap::standard_library::vector_type<data_list>("DataList"));

//    std::cout << "=== opening a state ===" << std::endl;
//
//    sol::state lua;
//    // open some common libraries
//    lua.open_libraries(sol::lib::base, sol::lib::package);
//    lua.script("print('bark bark bark!')");
//
//    std::cout << std::endl;

    return 0;
}
