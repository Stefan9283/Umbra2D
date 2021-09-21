#ifndef UMBRA2D_AUDIOPLAYER_H
#define UMBRA2D_AUDIOPLAYER_H

#include "myFileHandler.h"

typedef struct {
    SoundFile *soundFile;
    unsigned long fileCursor;
    bool isLooped;
} SoundQueueItem;

namespace Umbra2D {
    class AudioPlayer {
    public:
        AudioPlayer();
        ~AudioPlayer();
        void play(const string& name, bool loop);
    private:
        std::vector<SoundQueueItem *> soundQueue;
        PaStream *stream = nullptr;
        myFileHandler fileHandler;
        static PaStreamParameters getMyDefaultOutParams(PaDeviceIndex index);
        static int callback(const void* input, void* output, unsigned long frameCount,
                     const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);
    };
}


#endif
