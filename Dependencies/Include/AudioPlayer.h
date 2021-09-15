#ifndef UMBRA2D_AUDIOPLAYER_H
#define UMBRA2D_AUDIOPLAYER_H
#endif

#include "Common.h"

#define FRAMES_PER_BUFFER   (512)

typedef struct {
    SNDFILE* wav;
    SF_INFO info;
} myWav;

namespace Umbra2D {
    class AudioPlayer {
    private:
        bool initialised = false;
        std::unordered_map<std::string, myWav*> audioDatabase;
    public:
        AudioPlayer();
        ~AudioPlayer();

        [[nodiscard]] bool canPlayAudio() const;
        void addAudio(const char *path, const std::string& name);
        myWav *getAudio(const std::string& name);

        void listOutputDevices() ;

        PaError defaultPlayAudio(const std::string& name);

        PaError playAudio(const std::string &name, PaDeviceIndex deviceIndex);
    };
}
