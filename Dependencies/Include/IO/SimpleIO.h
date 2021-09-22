#ifndef UMBRA2D_SIMPLEIO_H
#define UMBRA2D_SIMPLEIO_H
#include "Common.h"

namespace Umbra2D::IO {
    using namespace std;
    void loadFile(string& saveHere, const string& path);
    void saveFile(string& saveThis, const string& path);
}

#endif //UMBRA2D_SIMPLEIO_H
