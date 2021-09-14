// Umbra2D headers
#define STB_IMAGE_IMPLEMENTATION

#include "Common.h"
#include "AssetLibrary.h"
#include "Window.h"
#include "Entity.h"
#include "Texture.h"
#include "Fonts.h"
#include "Graphics/Shader.h"
#include "Graphics/FrameBuffer.h"
#include "Gui/Gui.h"
#include "Gui/FileExplorer.h"
#include "Components/Camera.h"
#include "Components/Colliders.h"
#include "Components/Component.h"
#include "Components/Renderable.h"
#include <Engines/Engine.h>

Umbra2D::Engine* umbra;
Umbra2D::Shader* colliderShader;

int main() {
//    chaiscript::ChaiScript chai;
//
//
    umbra = new Umbra2D::Engine();
    umbra->loadProject();

    Umbra2D::Gui::FileExplorer fe;

    colliderShader = new Umbra2D::Shader("Dependencies/Shader/collider/vert.glsl", "Dependencies/Shader/collider/frag.glsl");
    Umbra2D::Shader spriteShader("Dependencies/Shader/sprite/vert.glsl", "Dependencies/Shader/sprite/frag.glsl");
    Umbra2D::Shader textShader("Dependencies/Shader/text/vert.glsl", "Dependencies/Shader/text/frag.glsl");

    textShader.setMat4("model", glm::mat4(1));

    Umbra2D::Components::Camera editorCamera(WINDOW);

    auto character = new Umbra2D::Entity;
//    character.setSpriteSheet("Dependencies/Assets/Textures/Adventurer/adventurer-Sheet.png");
//    character.transform.scale = 15.f * glm::vec2(43, 37);
//    character.transform.layer = 1;
//
//    Umbra2D::Static bg;
//    bg.setTexture("Dependencies/Assets/Textures/UndertaleFin.png");
//    bg.transform.scale = glm::vec2(10000, 10000);
//    bg.transform.layer = 2;
//
//    auto* rectangle = new Umbra2D::Colliders::Rectangle(200, 100);
//    auto* circle = new Umbra2D::Colliders::Circle(200);
//    auto* line = new Umbra2D::Colliders::Line(100, glm::vec2(1, 1));
//
//    Umbra2D::Text::Font f("Dependencies/Assets/Fonts/Minecraft.ttf");
//
//    std::string renderedString = "Bruh";
//
//
    Umbra2D::FrameBuffer frbuf(GL_RGBA, {1920, 1080});
    frbuf.unbind();

//    ImGui::GetIO().ConfigWindowsResizeFromEdges = true;
//
//    int colliderDepth = 0;
    while (!WINDOW->shouldClose()) {
        WINDOW->startFrame();

        static bool use_work_area = true;
        ImGuiWindowFlags rootFlags =
                    ImGuiWindowFlags_NoMove
                    | ImGuiWindowFlags_NoCollapse
                    | ImGuiWindowFlags_NoDocking
                    | ImGuiWindowFlags_NoResize
                    | ImGuiWindowFlags_NoTitleBar
                    | ImGuiWindowFlags_MenuBar
                    | ImGuiWindowFlags_NoBackground
                    | ImGuiWindowFlags_NoBringToFrontOnFocus;

        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
        ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

        ImGui::Begin("RootWindow", (bool*)use_work_area, rootFlags);
        ImGui::DockSpace(ImGui::GetID("MainWindow"));
        {   // WRITE YOUR CODE INSIDE OF THESE BRACKETS
            fe.showFileExplorer();

            // check out what this function does for more ImGui examples
            ImGui::ShowDemoWindow();

            if(ImGui::Begin("Utils")) {
//                LIBRARY->gui();
//
//                // ENTITIES
//                if (ImGui::TreeNode("bg")) {
//                    bg.gui();
//                    ImGui::TreePop();
//                }
//                if (ImGui::TreeNode("character")) {
//                    character.gui();
//                    ImGui::TreePop();
//                }
//
//                // COLLIDERS
//                if (ImGui::TreeNode("colliders")) {
//                    if (ImGui::TreeNode("line")) {
//                        line->gui();
//                        ImGui::TreePop();
//                    }
//                    if (ImGui::TreeNode("circle")) {
//                        circle->gui();
//                        ImGui::TreePop();
//                    }
//                    if (ImGui::TreeNode("rectangle")) {
//                        rectangle->gui();
//                        ImGui::TreePop();
//                    }
//                    ImGui::SliderInt("colliders depth", &colliderDepth, 0, 1000);
//                    ImGui::TreePop();
//                }
//                ImGui::InputText("Rendered Text ", &renderedString);
//
//                editorCamera.gui();
            }
            ImGui::End();


            // ACTUAL RENDERING TO FRAMEBUFFER
            frbuf.bind();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//            editorCamera.UpdateProjMatrix();
//            glm::mat4
//                    proj = editorCamera.getProj(),
//                    view = editorCamera.getView();
//
//            // ENTITIES RENDERING
//            spriteShader.setMat4("view", &view);
//            spriteShader.setMat4("proj", &proj);
//
//            bg.draw(&spriteShader);
//            character.draw(&spriteShader);
//
//            // TEXT RENDERING
//            textShader.setMat4("view", &view);
//            textShader.setMat4("proj", &proj);
//            f.RenderText(&textShader, renderedString, 0, 0, 1.0f,glm::vec4(0.5, 0.8f, 0.2f, 1.f), 0);
//
//            colliderShader->setMat4("view", &view);
//            colliderShader->setMat4("proj", &proj);
//            colliderShader->setFloat("depth", colliderDepth);
//
//            circle->draw();
////            line->draw();
////            rectangle->draw();
//
            frbuf.unbind();

            // DRAW GAME FRAMEBUFFER AS IMGUI TEXTURE
            if (ImGui::Begin("Game", (bool*)true, ImGuiWindowFlags_NoScrollbar)) {
                ImVec2 windowSize = ImGui::GetWindowSize();

                auto targetResolution = glm::vec2(windowSize.x, windowSize.y);
                glm::vec2 resolution = frbuf.getTexture()->getResolution();

                float ratio = resolution.x / resolution.y;

                glm::vec2 mostICanDo;

                mostICanDo.x = ratio * targetResolution.y;
                mostICanDo.y = targetResolution.x / ratio;

                glm::vec2 newResolution;

                if (mostICanDo.x < targetResolution.x) {
                    newResolution = glm::vec2(mostICanDo.x, targetResolution.y);
                } else {
                    newResolution = glm::vec2(targetResolution.x, mostICanDo.y);
                }

                ImVec2 pos = ImGui::GetCursorScreenPos();
                ImGui::SetCursorPos(ImVec2((windowSize.x - newResolution.x) / 2, (windowSize.y - newResolution.y) / 2));
                Umbra2D::Gui::showTexture(frbuf.getTexture(), targetResolution);
                ImVec2 pos2 = ImGui::GetCursorScreenPos();

                if (ImGui::IsItemHovered()) {
                    ImGui::BeginTooltip();
                    ImGuiIO& io = ImGui::GetIO();
                    auto posOnViewPort = glm::vec2(io.MousePos.x - pos.x, pos2.y - io.MousePos.y - ImGui::GetStyle().ItemSpacing.y);
                    ImGui::Text("Coords %f, %f", posOnViewPort.x, posOnViewPort.y);
                    ImGui::Text("Resolution %f, %f", newResolution.x, newResolution.y);

                    auto normalizedCoords = (2.f * posOnViewPort - newResolution) / newResolution;

                    ImGui::Text("Coords in [-1, 1] %f, %f", normalizedCoords.x, normalizedCoords.y);
                    auto worldCoords = editorCamera.getWorldCoords(normalizedCoords);
                    ImGui::Text("World Coordinates %f, %f", worldCoords.x, worldCoords.y);
                    ImGui::EndTooltip();
                }
            }
            ImGui::End();

            // CAMERA INPUTS VIA WINDOW INSTANCE
            if (WINDOW->wasKeyPressed(GLFW_KEY_ESCAPE))
                break;
////            if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows))
//            {
//                float unitsPerFrame = 5;
//                if (WINDOW->wasKeyPressed(GLFW_KEY_D))
//                    editorCamera.MoveHorizontally(-unitsPerFrame);
//                if (WINDOW->wasKeyPressed(GLFW_KEY_A))
//                    editorCamera.MoveHorizontally(unitsPerFrame);
//                if (WINDOW->wasKeyPressed(GLFW_KEY_W))
//                    editorCamera.MoveVertically(unitsPerFrame);
//                if (WINDOW->wasKeyPressed(GLFW_KEY_S))
//                    editorCamera.MoveVertically(-unitsPerFrame);
//                if (WINDOW->wasKeyPressed(GLFW_KEY_LEFT_CONTROL))
//                    editorCamera.Zoom(0.01f);
//                if (WINDOW->wasKeyPressed(GLFW_KEY_LEFT_ALT))
//                    editorCamera.Zoom(-0.01f);
//            }
        } // WRITE YOUR CODE INSIDE OF THESE BRACKETS


        ImGui::End();
        WINDOW->endFrame();
    }
//    delete colliderShader;
//
    umbra->saveProject();
    delete umbra;

    return 0;
}
