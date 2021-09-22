#include "IO/SimpleIO.h"

namespace Umbra2D::IO {
    void loadFile(string& saveHere, const string& path) {
        ifstream file(path);
        string str;
        saveHere = "";
        while (getline(file, str))
            saveHere += str + "\n";
    }
    void saveFile(string& saveThis, const string& path) {
        ofstream file(path);
        file << saveThis;
    }
}