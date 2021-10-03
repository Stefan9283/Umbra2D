#include "Umbra2D.h"

namespace Umbra2D {
    Umbra2DEngine::Umbra2DEngine() {
        w = new Umbra2D::Window;
        lib = new Umbra2D::AssetLibrary;
        scene = new Scene;
        logger = new Umbra2D::Gui::Logger;
        settings = new Umbra2D::Gui::EngineSettings;
    }
    Umbra2DEngine::~Umbra2DEngine() {
        delete lib;
        delete w;
        delete colliderShader;
        delete scene;
        delete logger;
        delete settings;
    }
    void Umbra2DEngine::loadProject() {
        Umbra2D::IO::Loader loader("Projects/Saves.txt");
        loader.parseInputFile();
    }
    void Umbra2DEngine::saveProject() {
        Umbra2D::IO::Saver saver("Projects/Saves.txt");
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

        logger->addLog("status", "The Engine is ready to go!");

        // TODO don't generate entity, shader or renderer objects in this func. It should be done in the GUI
//        auto bg = scene->addEntity("background");
//        bg->addComponent<STATIC>()->setTexture("Dependencies/Assets/Textures/UndertaleFin.png");
//        auto t = bg->addComponent<TRANSFORM>();
//        t->scale = {2000, 1000};
//        t->layer = 100;

//        auto camera = scene->addEntity("camera");
//        camera->addComponent<CAMERA>(w);

//        auto hero1 = scene->addEntity("hero1");
//        hero1->addComponent<DYNAMIC>()->setSpriteSheet("Dependencies/Assets/Textures/Adventurer/adventurer-Sheet.png", glm::vec2(7, 11), 72, "adventurer");
//        hero1->addComponent<TRANSFORM>()->translation = {-100, 0};
//        auto c1 = hero1->addComponent<CIRCLE>(200.f);
//
//        auto hero2 = scene->addEntity("hero2");
//        hero2->addComponent<DYNAMIC>()->setSpriteSheet("Dependencies/Assets/Textures/Adventurer/adventurer-Sheet.png", glm::vec2(7, 11), 72, "adventurer");
//        hero2->addComponent<TRANSFORM>()->translation = {0, 0};
//        auto c2 = hero2->addComponent<AARECTANGLE>(200.f, 100.f);
//
//        auto hero3 = scene->addEntity("hero3");
//        hero3->addComponent<DYNAMIC>()->setSpriteSheet("Dependencies/Assets/Textures/Adventurer/adventurer-Sheet.png", glm::vec2(7, 11), 72, "adventurer");
//        hero3->addComponent<TRANSFORM>()->translation = {100, 0};
//        auto c3 = hero3->addComponent<LINE>(100.f, glm::vec2(0, 1), glm::vec2(0, 0));


        Graphics::GraphicsPipeline ppl;
        ppl.addRenderPass((new Graphics::OneTypeVoidPass<DYNAMIC>)->setFrameBuffer(glm::ivec2(1920, 1080)));

        while (!w->shouldClose()) {
            if (w->wasKeyPressed(GLFW_KEY_ESCAPE))
                break;

            w->startFrame();

//            if (ImGui::Begin("Collisions")) {
//                ImGui::Text("c1 - c2 %d", c1->checkCollision(c2));
//                ImGui::Text("c1 - c3 %d", c3->checkCollision(c1));
//                ImGui::Text("c2 - c3 %d", c3->checkCollision(c2));
//            }
//            ImGui::End();

            edit.setFrameBuffer(ppl.getDrawnFrameBuffer(edit.getCamera(), scene));

            ppl.gui();
            fe.gui();
            logger->gui();
            settings->gui();
            scene->gui();
            lib->gui();
            edit.gui();

            ImGui::ShowDemoWindow();

            w->endFrame();
        }
        saveProject();
    }

    glm::vec4 Umbra2DEngine::getThemeColor() { return settings->getColor(); }
}
