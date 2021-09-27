#include "Umbra2D.h"

namespace Umbra2D {
    Umbra2DEngine::Umbra2DEngine() {
        w = new Umbra2D::Window;
        lib = new Umbra2D::AssetLibrary;
        colliderShader = (new SHADER)->loadShader("shader1", "Dependencies/Shader/collider/vert.glsl", "Dependencies/Shader/collider/frag.glsl");
        scene = new Scene;
        theme = new Gui::ImGuiTheme(glm::vec4(0.5, 0, 0, 1));
        logger = new Umbra2D::Gui::Logger;
    }
    Umbra2DEngine::~Umbra2DEngine() {
        delete lib;
        delete w;
        delete colliderShader;
        delete scene;
        delete theme;
        delete logger;
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
        Umbra2D::Renderer renderer;
        Umbra2D::CollidersRenderer collidersRenderer;

        Umbra2D::Graphics::Shader spriteShader;
        spriteShader.loadShader("shader2", "Dependencies/Shader/sprite/vert.glsl", "Dependencies/Shader/sprite/frag.glsl");
        Umbra2D::Graphics::Shader textShader;
        textShader.loadShader("shader3", "Dependencies/Shader/text/vert.glsl", "Dependencies/Shader/text/frag.glsl");

        auto bg = scene->addEntity("background");
        bg->addComponent<STATIC>()->setTexture("Dependencies/Assets/Textures/UndertaleFin.png");
        auto t = bg->addComponent<TRANSFORM>();
        t->scale = {2000, 1000};
        t->layer = 100;

//        auto camera = scene->addEntity("camera");
//        camera->addComponent<CAMERA>(w);


        auto hero1 = scene->addEntity("hero1");
        hero1->addComponent<DYNAMIC>()->setSpriteSheet("Dependencies/Assets/Textures/Adventurer/adventurer-Sheet.png", glm::vec2(7, 11), 72, "adventurer");
        hero1->addComponent<TRANSFORM>()->translation = {-100, 0};
        auto c1 = hero1->addComponent<CIRCLE>(200.f);

        auto hero2 = scene->addEntity("hero2");
        hero2->addComponent<DYNAMIC>()->setSpriteSheet("Dependencies/Assets/Textures/Adventurer/adventurer-Sheet.png", glm::vec2(7, 11), 72, "adventurer");
        hero2->addComponent<TRANSFORM>()->translation = {0, 0};
        hero2->addComponent<TRANSFORM>()->translation = {0, 0};
        auto c2 = hero2->addComponent<AARECTANGLE>(200.f, 100.f);

        auto hero3 = scene->addEntity("hero3");
        hero3->addComponent<DYNAMIC>()->setSpriteSheet("Dependencies/Assets/Textures/Adventurer/adventurer-Sheet.png", glm::vec2(7, 11), 72, "adventurer");
        hero3->addComponent<TRANSFORM>()->translation = {100, 0};
        auto c3 = hero3->addComponent<LINE>(100.f, glm::vec2(0, 1), glm::vec2(0, 0));


        Graphics::GraphicsPipeline ppl;
        ppl.addRenderPass((new Graphics::RenderPass)->setType(Void )->setFrameBuffer(glm::ivec2(1920, 1080)));
        ppl.addRenderPass((new Graphics::RenderPass)->setType(FrBuf)->setFrameBuffer(glm::ivec2(1920, 1080)));
        ppl.addRenderPass((new Graphics::RenderPass)->setType(Adder)->setFrameBuffer(glm::ivec2(1920, 1080)));

        while (!w->shouldClose()) {
            if (w->wasKeyPressed(GLFW_KEY_ESCAPE))
                break;

            w->startFrame();

            if (ImGui::Begin("Collisions")) {
                ImGui::Text("c1 - c2 %d", c1->checkCollision(c2));
                ImGui::Text("c1 - c3 %d", c3->checkCollision(c1));
                ImGui::Text("c2 - c3 %d", c3->checkCollision(c2));
            }
            ImGui::End();

            ppl.gui();

            fe.gui();
            edit.gui();
            logger->gui();
            ImGui::ShowDemoWindow();
            theme->gui();
            scene->gui();
            lib->gui();

            edit.startRender();

            spriteShader.setMat4("proj", edit.getProj());
            spriteShader.setMat4("view", edit.getView());

            colliderShader->setMat4("proj", edit.getProj());
            colliderShader->setMat4("view", edit.getView());

            // add here your render passes
            collidersRenderer.onUpdate(scene, colliderShader);
            renderer.onUpdate(scene, &spriteShader);

            edit.stopRender();

            w->endFrame();
        }
        saveProject();



    }

    glm::vec4 Umbra2DEngine::getThemeColor() { return theme->getColor(); }
}
