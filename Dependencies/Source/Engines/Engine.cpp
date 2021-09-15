#include <Gui/Editor.h>
#include <Engines/Renderer.h>
#include "Engines/Engine.h"
#include "AssetLibrary.h"
#include "Window.h"
#include "IO/Loader.h"
#include "IO/Saver.h"
#include "Graphics/Shader.h"
#include "Gui/FileExplorer.h"
#include "Scene.h"

namespace Umbra2D {
    Umbra2DEngine::Umbra2DEngine() {
        w = new Umbra2D::Window;
        lib = new Umbra2D::AssetLibrary;
        colliderShader = new Umbra2D::Shader("Dependencies/Shader/collider/vert.glsl", "Dependencies/Shader/collider/frag.glsl");
        scene = new Scene;
        theme = new Gui::ImGuiTheme(glm::vec4(0.5, 0, 0, 1));
    }
    Umbra2DEngine::~Umbra2DEngine() {
        delete lib;
        delete w;
        delete colliderShader;
        delete scene;
    }
    void Umbra2DEngine::loadProject() {
        Umbra2D::Loader loader("Projects/Saves.txt");
        loader.parseInputFile();
    }
    void Umbra2DEngine::saveProject() {
        Umbra2D::Saver saver("Projects/Saves.txt");
        saver.saveSettings();
    }

    Umbra2D::AssetLibrary* Umbra2DEngine::getLibrary() {
        if (!lib)
            lib = new Umbra2D::AssetLibrary();
        return lib;
    }
    Umbra2D::Window* Umbra2DEngine::getWindow() {
        if (!w)
            w = new Umbra2D::Window();
        return w;
    }

    void Umbra2DEngine::run() {
        loadProject();
        Umbra2D::Gui::FileExplorer fe;
        Umbra2D::Gui::Editor edit(w);
        Umbra2D::Renderer r;

        Umbra2D::Shader spriteShader("Dependencies/Shader/sprite/vert.glsl", "Dependencies/Shader/sprite/frag.glsl");
        Umbra2D::Shader textShader("Dependencies/Shader/text/vert.glsl", "Dependencies/Shader/text/frag.glsl");

        while (!w->shouldClose()) {
            if (w->wasKeyPressed(GLFW_KEY_ESCAPE))
                break;
            w->startFrame();
            theme->gui();
            fe.showFileExplorer();
            edit.startRender();
            r.onUpdate(scene, &spriteShader);
            edit.stopRender();
            edit.gui();
            ImGui::ShowDemoWindow();

            w->endFrame();
        }

        saveProject();
    }

    glm::vec4 Umbra2DEngine::getThemeColor() {
        return theme->getColor();
    }
}
