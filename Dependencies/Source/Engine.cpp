#include "Engine.h"
#include "AssetLibrary.h"
#include "Window.h"
#include "Loader.h"
#include "Saver.h"

namespace Umbra2D {
    Engine::Engine() {
        w = new Umbra2D::Window();
        lib = new Umbra2D::AssetLibrary();
    }
    Engine::~Engine() {
        delete w;
        delete lib;
    }
    void Engine::loadProject() {
        Umbra2D::Loader loader("Projects/Saves.txt");
        loader.parseInputFile();
    }
    void Engine::saveProject() {
        Umbra2D::Saver saver("Projects/Saves.txt");
        saver.saveSettings();
    }

    Umbra2D::AssetLibrary* Engine::getLibrary() {
        if (!lib)
            lib = new Umbra2D::AssetLibrary();
        return lib;
    }
    Umbra2D::Window* Engine::getWindow() {
        if (!w)
            w = new Umbra2D::Window();
        return w;
    }
};