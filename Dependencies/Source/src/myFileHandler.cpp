#include "include/myFileHandler.h"

namespace Umbra2D {

    myFileHandler::myFileHandler() :soundLibrary() {
        openSound(R"(C:\Users\soulv\Documents\GitHub\Umbra2D\Dependencies\Assets\sounds\test.wav)", "test");
        openSound(R"(C:\Users\soulv\Documents\GitHub\Umbra2D\Dependencies\Assets\sounds\loop.wav)", "loop");
        openSound(R"(C:\Users\soulv\Documents\GitHub\Umbra2D\Dependencies\Assets\sounds\Powerup47.wav)", "short");
    }

    myFileHandler::~myFileHandler() {
        for(const auto& soundFile : soundLibrary)
            sf_close(soundFile.second->audio);
    }

    SoundFile *myFileHandler::getSound(const string& name) {
        auto searchedSound = soundLibrary.find(name);
        if(searchedSound != soundLibrary.end()) {
            return searchedSound->second;
        }
        else
            fprintf(stderr, "The soundFile named %s does not exist!\n", name.c_str());
        return nullptr;
    }

    void myFileHandler::openSound(const string& path, const string& name) {
        auto *added_file = new SoundFile;
        added_file->info.format = 0;
        added_file->audio = sf_open(path.c_str(), SFM_READ, &added_file->info);
        if (sf_error(added_file->audio) != SF_ERR_NO_ERROR) {
            fprintf(stderr, "%s\nFile: %s\n", sf_strerror(added_file->audio), path.c_str());
            return;
        }
        if(!soundLibrary.contains(name)) {
            soundLibrary[name] = added_file;
        }
        else
            fprintf(stderr, "The soundFile named %s already exists!\n", name.c_str());
   }
}
