#include "Umbra2D.h"

namespace Umbra2D::Audio {
    AudioPlayer::AudioPlayer() : fileHandler() {
        PaError error = Pa_Initialize();
        if (error != paNoError) {
            fprintf(stderr, "Problem initialising PortAudio!\n");
        }
        else {
            PaDeviceIndex defaultIndex = Pa_GetDefaultOutputDevice();
            if(defaultIndex == paNoDevice)
                fprintf(stderr, "No default device\n");
            else {
                PaStreamParameters hostApiOutputParameters = getMyDefaultOutParams(defaultIndex);
                error = Pa_OpenStream(&stream, nullptr, &hostApiOutputParameters, 44000,
                                      1024, paNoFlag, callback, this);
                if (error != paNoError) {
                    fprintf(stderr, "Problem opening Default Stream\n");
                }
                error = Pa_StartStream(stream);
                if (error != paNoError) {
                    fprintf(stderr, "Problem opening starting Stream\n");
                }
            }
        }
    }

    AudioPlayer::~AudioPlayer() {
        if (Pa_StopStream(stream) != paNoError) {
            fprintf(stderr, "Problem closing stream\n");
        }
        if (Pa_Terminate() != paNoError) {
            fprintf(stderr, "Problem closing stream\n");
        }
    }

    PaStreamParameters AudioPlayer::getMyDefaultOutParams(PaDeviceIndex index) {
        PaStreamParameters hostApiOutputParameters;
        hostApiOutputParameters.device = index;
        hostApiOutputParameters.channelCount = 2;
        hostApiOutputParameters.sampleFormat = paFloat32;
        hostApiOutputParameters.suggestedLatency = 0.01;
        hostApiOutputParameters.hostApiSpecificStreamInfo = nullptr;
        return hostApiOutputParameters;
    }

    void AudioPlayer::play(const string& name, bool loop) {
        soundQueue.push_back(new SoundQueueItem {
                fileHandler.getSound(name), 0, loop});
    }

    int AudioPlayer::callback(const void* input, void* output, unsigned long frameCount,
                              const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {

        (void) input;
        (void) timeInfo;
        (void) statusFlags;

        unsigned long stereoFrames = frameCount * 2;
        auto *streamHandler = (AudioPlayer *) userData;
        memset((float *) output, 0, sizeof(float) * stereoFrames);

        auto currentIterator = streamHandler->soundQueue.begin();
        auto deleteIterator = streamHandler->soundQueue.begin();
        while(currentIterator != streamHandler->soundQueue.end()) {
            SoundQueueItem *currentItem = (*currentIterator);
            auto *currentSound = currentItem->soundFile;

            auto outputBuffer = new float[stereoFrames];
            float *bufferCursor = outputBuffer;
            unsigned long framesRead;
            int noChannels = currentSound->info.channels;

            while(true) {
                sf_seek(currentSound->audio, currentItem->fileCursor, SEEK_SET);
                framesRead = (unsigned long) sf_readf_float(currentSound->audio, bufferCursor, frameCount);

                if(framesRead == 0) {
                    if(currentItem->isLooped) {
                        sf_seek(currentSound->audio, 0, SEEK_SET);
                        currentItem->fileCursor = 0;
                    }
                    else
                        currentIterator = streamHandler->soundQueue.erase(currentIterator);
                    break;
                } else {
                    currentItem->fileCursor += framesRead;
                    if(framesRead == frameCount)
                        break;
                    else
                        bufferCursor = bufferCursor + framesRead;
                }
            }

            auto outputCursor = (float *) output;
            if(noChannels == 1) {
                for(unsigned long i = 0; i < stereoFrames; i+=2) {
                    outputCursor[i] += outputBuffer[i];
                    outputCursor[i+1] += outputBuffer[i];
                }
            } else if(noChannels == 2) {
                for(unsigned long i = 0; i < stereoFrames; i++)
                    outputCursor[i] = outputCursor[i] + outputBuffer[i];
            }
            if(framesRead != 0)
                ++currentIterator;
        }
        return paContinue;
    }
}
