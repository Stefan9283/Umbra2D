#ifndef UMBRA2D_MYFILEHANDLER_H
#define UMBRA2D_MYFILEHANDLER_H

#include "Common.h"
using std::string;

struct SoundFile {
    SNDFILE* audio;
    SF_INFO info;
};

namespace Umbra2D::Audio {
    class myFileHandler {
    public:
        myFileHandler();
        ~myFileHandler();
        SoundFile *getSound(const string& name);
    private:
        std::unordered_map<string, SoundFile *> soundLibrary;
        void openSound(const string& path, const string& name);
    };
}

#endif //UMBRA2D_MYFILEHANDLER_H