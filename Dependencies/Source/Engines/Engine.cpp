#include "AssetLibrary.h"
#include "Window.h"
#include "Scene.h"
#include "Entity.h"
#include "Engines/Engine.h"
#include "Engines/Renderer.h"
#include "IO/Saver.h"
#include "IO/Loader.h"
#include "Graphics/Shader.h"
#include "Gui/Editor.h"
#include "Gui/FileExplorer.h"
#include "Components/Camera.h"
#include "Components/Renderable.h"

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

        Umbra2D::Renderer renderer;

        Umbra2D::Shader spriteShader("Dependencies/Shader/sprite/vert.glsl", "Dependencies/Shader/sprite/frag.glsl");
        Umbra2D::Shader textShader("Dependencies/Shader/text/vert.glsl", "Dependencies/Shader/text/frag.glsl");

        auto bg = scene->addEntity("background");
        bg->addComponent<STATIC>()->setTexture("Dependencies/Assets/Textures/UndertaleFin.png");

        auto camera = scene->addEntity("camera");

//        camera->addComponent<CAMERA>(w);

        while (!w->shouldClose()) {
            if (w->wasKeyPressed(GLFW_KEY_ESCAPE))
                break;
            w->startFrame();

            fe.gui();
            //edit.gui();

            //ImGui::ShowDemoWindow();

            theme->gui();
            scene->gui();
            lib->gui();

            edit.startRender();

            spriteShader.setMat4("proj", edit.getProj());
            spriteShader.setMat4("view", edit.getView());

            // add here your render passes
            renderer.onUpdate(scene, &spriteShader);

            edit.stopRender();

            w->endFrame();
        }

        saveProject();
    }

    glm::vec4 Umbra2DEngine::getThemeColor() { return theme->getColor(); }
}
