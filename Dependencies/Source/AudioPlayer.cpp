#include "AudioPlayer.h"

static int callback(const void* input, void* output, unsigned long frameCount,
     const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
{
    auto* out = (float*) output;
    auto* passed_wav = (myWav*) userData;

    memset(out, 0, sizeof(float) * frameCount * passed_wav->info.channels);

    if (sf_read_float(passed_wav->wav, out, frameCount * passed_wav->info.channels) < frameCount) {
        return paComplete;
    }

    return paContinue;
}

namespace Umbra2D {
    AudioPlayer::AudioPlayer() {
        initialised = (Pa_Initialize() == paNoError);
    }

    AudioPlayer::~AudioPlayer() {
        for(const auto& audio : audioDatabase)
            sf_close(audio.second->wav);
        if(Pa_Terminate() != paNoError)
            fprintf(stderr, "%s\n", "PortAudio could not be terminated!");
    }

    bool AudioPlayer::canPlayAudio() const {
        return initialised;
    }

    void AudioPlayer::addAudio(const char *path,const std::string& name) {
        auto *added_wav = new myWav;
        added_wav->wav = sf_open(path, SFM_READ, &added_wav->info);
        if (sf_error(added_wav->wav) != SF_ERR_NO_ERROR) {
            fprintf(stderr, "%s\n", sf_strerror(added_wav->wav));
            fprintf(stderr, "File: %s\n", "test.wav");
            return;
        }
        audioDatabase[name] = added_wav;
    }

    myWav *AudioPlayer::getAudio(const std::string& name) {
        auto a = audioDatabase.find(name);
        if(a == audioDatabase.end())
            return nullptr;
        else
            return a->second;
    }

    PaError AudioPlayer::defaultPlayAudio(const std::string& name) {
        return playAudio(name, Pa_GetDefaultOutputDevice());
    }

    PaError AudioPlayer::playAudio(const std::string& name, PaDeviceIndex deviceIndex) {

        myWav *current_wav = getAudio(name);
        if(current_wav == nullptr) {
            fprintf(stderr, "Non-existent audio!\n");
            return -1;
        }

        PaError error = Pa_Initialize();
        if (error != paNoError) {
            fprintf(stderr, "Problem initializing!\n");
            return error;
        }

        PaStream* stream;
        PaStreamParameters hostApiOutputParameters;
        hostApiOutputParameters.device = deviceIndex;
        if( hostApiOutputParameters.device == paNoDevice)
            return paDeviceUnavailable;

        hostApiOutputParameters.channelCount = current_wav->info.channels;
        hostApiOutputParameters.sampleFormat = paFloat32;
        hostApiOutputParameters.suggestedLatency = Pa_GetDeviceInfo(deviceIndex)->defaultHighOutputLatency;
        hostApiOutputParameters.hostApiSpecificStreamInfo = nullptr;

        error = Pa_OpenStream(&stream, nullptr, &hostApiOutputParameters, current_wav->info.samplerate,
                              FRAMES_PER_BUFFER, paNoFlag, callback, current_wav);

        if (error != paNoError) {
            fprintf(stderr, "Problem opening Default Stream\n");
            return error;
        }

        error = Pa_StartStream(stream);
        if (error != paNoError) {
            fprintf(stderr, "Problem opening starting Stream\n");
            return error;
        }

        while (Pa_IsStreamActive(stream)) {
            Pa_Sleep(100);
        }

        error = Pa_StopStream(stream);
        if (error != paNoError) {
            fprintf(stderr, "Problem closing stream\n");
            return error;
        }

        return paNoError;
    }

    void AudioPlayer::listOutputDevices() {
        PaDeviceIndex defaultIndex = Pa_GetDefaultOutputDevice();
        if(defaultIndex == paNoDevice)
            fprintf(stderr, "%s\n", "No default output device is available or an error was encountered!");
        else
            printf("The default device's index: %d\n", defaultIndex);
        int numDevices;
        numDevices = Pa_GetDeviceCount();
        if(numDevices < 0) {
            fprintf(stderr, "%s\n", "PortAudio is not initialized or an error is encountered");
            return;
        }
        for(auto i = 0; i < numDevices; i++ )
            if(Pa_GetDeviceInfo(i)->maxOutputChannels != 0)
                printf("%d : %s\n", i, Pa_GetDeviceInfo(i)->name);
    }
};
