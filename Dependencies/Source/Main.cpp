// Umbra2D headers
#define STB_IMAGE_IMPLEMENTATION
#include "Common.h"
#include "AssetLibrary.h"
#include "Window.h"
#include "Camera.h"
#include "Entity.h"
#include "Texture.h"
#include "Shader.h"
#include "Gui.h"
#include "Colliders.h"
#include "Loader.h"
#include "Saver.h"
#include "FileExplorer.h"

Umbra2D::AssetLibrary* lib;
Umbra2D::Shader* colliderShader;

int main() 
{
    Umbra2D::Window w;

    Umbra2D::FileExplorer fe;

    colliderShader = new Umbra2D::Shader("Dependencies/Shader/collider/vert.glsl", "Dependencies/Shader/collider/frag.glsl");
    Umbra2D::Shader spriteShader("Dependencies/Shader/sprite/vert.glsl", "Dependencies/Shader/sprite/frag.glsl");

    Umbra2D::Loader loader("Projects/Saves.txt");
    loader.parseInputFile();

    Umbra2D::Camera editorCamera(&w);

    Umbra2D::Dynamic character;
    character.setSpriteSheet("Dependencies/Assets/Textures/Adventurer/adventurer-Sheet.png");
    character.transform.scale = 15.f * glm::vec2(43, 37);
    character.pixelateLevel = 500;

    Umbra2D::Static bg;
    bg.setTexture("Dependencies/Assets/Textures/UndertaleFin.png");
    bg.transform.scale = glm::vec2(10000, 10000);
    bg.transform.layer = 3;

    unsigned int spriteIndex = 0;
    glm::vec2 start{}, end{1, 1};

    auto* rectangle = new Umbra2D::Colliders::Rectangle(200, 100);
    auto* circle = new Umbra2D::Colliders::Circle(200);
    auto* line = new Umbra2D::Colliders::Line(1, glm::vec2(-1, 0));

    while (!w.shouldClose()) {
        w.startFrame();

        // code 
        // lib->gui();
        fe.showFileExplorer();

        // check out what this function does for more ImGui examples
        // ImGui::ShowDemoWindow(); 
        
        /*editorCamera.UpdateProjMatrix();
        glm::mat4 proj, view;
        proj = editorCamera.getProj();
        view = editorCamera.getView();

        spriteShader.setMat4("view", &view);
        spriteShader.setMat4("proj", &proj);
        if (ImGui::TreeNode("bg")) {
            bg.gui();
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("character")) {
            character.gui();
            ImGui::TreePop();
        }*/
        // bg.draw(&spriteShader);
        // character.draw(&spriteShader);

        /*colliderShader->setMat4("view", &view);
        colliderShader->setMat4("proj", &proj);
        colliderShader->setInt("depth", 999);

        if (ImGui::TreeNode("colliders")) {
            if (ImGui::TreeNode("line")) {
                line->gui();
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("circle")) {
                circle->gui();
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("rectangle")) {
                rectangle->gui();
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }*/
//        circle->draw();
 //         line->draw();
//        rectangle->draw();


        /*if (!ImGui::IsWindowHovered()) {
            if (w.wasKeyPressed(GLFW_KEY_ESCAPE))
                break;
            float unitsPerFrame = 5;
            if (w.wasKeyPressed(GLFW_KEY_D))
                editorCamera.MoveHorizontally(-unitsPerFrame);
            if (w.wasKeyPressed(GLFW_KEY_A))
                editorCamera.MoveHorizontally(unitsPerFrame);
            if (w.wasKeyPressed(GLFW_KEY_W))
                editorCamera.MoveVertically(unitsPerFrame);
            if (w.wasKeyPressed(GLFW_KEY_S))
                editorCamera.MoveVertically(-unitsPerFrame);
            if (w.wasKeyPressed(GLFW_KEY_LEFT_CONTROL))
                editorCamera.Zoom(0.01f);
            if (w.wasKeyPressed(GLFW_KEY_LEFT_ALT))
                editorCamera.Zoom(-0.01f);
        }
        // code */
        
        w.endFrame();
    }

    /*Umbra2D::Saver saver("Projects/Saves.txt");
    saver.saveSettings();

    delete colliderShader;
    delete lib;*/
    
    return 0;
}