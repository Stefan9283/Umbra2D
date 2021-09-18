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
#include "Components/PropertyComponent.h"
#include "Components/Colliders.h"
#include "Texture.h"


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

        // TODO don't generate entity, shader or renderer objects in this func. It should be done in the GUI
        Umbra2D::Renderer renderer;
        Umbra2D::CollidersRenderer collidersRenderer;

        Umbra2D::Shader spriteShader("Dependencies/Shader/sprite/vert.glsl", "Dependencies/Shader/sprite/frag.glsl");
        Umbra2D::Shader textShader("Dependencies/Shader/text/vert.glsl", "Dependencies/Shader/text/frag.glsl");

//        auto bg = scene->addEntity("background");
//        bg->addComponent<STATIC>()->setTexture("Dependencies/Assets/Textures/UndertaleFin.png");
//        auto camera = scene->addEntity("camera");

//        camera->addComponent<CAMERA>(w);


            auto hero1 = scene->addEntity("hero1");
            hero1->addComponent<DYNAMIC>()->setSpriteSheet("Dependencies/Assets/Textures/Adventurer/adventurer-Sheet.png", glm::vec2(7, 11), 72, "adventurer");
            hero1->addComponent<TRANSFORM>()->setPos({-100, 0});
            auto c1 = hero1->addComponent<CIRCLE>(200.f);

            auto hero2 = scene->addEntity("hero2");
            hero2->addComponent<DYNAMIC>()->setSpriteSheet("Dependencies/Assets/Textures/Adventurer/adventurer-Sheet.png", glm::vec2(7, 11), 72, "adventurer");
            hero2->addComponent<TRANSFORM>()->setPos({0, 0});
            auto c2 = hero2->addComponent<AARECTANGLE>(200.f, 100.f);

            auto hero3 = scene->addEntity("hero3");
            hero3->addComponent<DYNAMIC>()->setSpriteSheet("Dependencies/Assets/Textures/Adventurer/adventurer-Sheet.png", glm::vec2(7, 11), 72, "adventurer");
            hero3->addComponent<TRANSFORM>()->setPos({100, 0});
            auto c3 = hero3->addComponent<LINE>(100.f, glm::vec2(0), glm::vec2(0, 0));


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

            // ImNodes
            if (ImGui::Begin("Nodes")) {
                ImNodes::BeginNodeEditor();

                int attribIndex = 0;
                int nodeIndex = 0;

                ImNodes::BeginNode(nodeIndex++);
                    ImNodes::BeginInputAttribute(attribIndex++);
                    ImGui::Text("Big Bruh");
                    ImNodes::EndInputAttribute();
                ImGui::SameLine();
                    ImNodes::BeginOutputAttribute(attribIndex++);
                    ImGui::Text("out");
                    ImNodes::EndOutputAttribute();
                ImNodes::EndNode();


                ImNodes::BeginNode(nodeIndex++);
                    ImNodes::BeginInputAttribute(attribIndex++);
                    ImGui::Text("Small Bruh");
                    ImNodes::EndInputAttribute();
                ImGui::SameLine();
                    ImNodes::BeginOutputAttribute(attribIndex++);
                    ImGui::Text("out 2");
                    ImNodes::EndOutputAttribute();
                ImNodes::EndNode();

                ImNodes::EndNodeEditor();

                int start_attr, end_attr;
                if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
                    std::cout << "Link (" << start_attr << ", " << end_attr << ") should have been created\n";
                }
                int link_id;
                if (ImNodes::IsLinkDestroyed(&link_id)) {
                }
            }
            ImGui::End();

            fe.gui();
            edit.gui();
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
