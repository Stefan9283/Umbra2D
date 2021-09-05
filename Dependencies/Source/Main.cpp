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

Umbra2D::AssetLibrary* lib;

int main() 
{
    Umbra2D::Window w;
    Umbra2D::Camera c(w);

    Umbra2D::Shader s("Dependencies/Shader/sprite/vert.glsl", "Dependencies/Shader/sprite/frag.glsl");
    
    lib->addSpriteSheet("Dependencies/Assets/Textures/Adventurer/adventurer-Sheet.png", glm::vec2(7, 11), 72);

    Umbra2D::Assets::SpriteSheet ss("Dependencies/Assets/Textures/Adventurer/adventurer-Sheet.png", glm::vec2(7, 11), 72);
    Umbra2D::Dynamic character;
    character.transform.scale = 15.f * glm::vec2(43, 37);
    character.pixelateLevel = 500;

    Umbra2D::Static bg;
    Umbra2D::Assets::Sprite bgtex("Dependencies/Assets/Textures/UndertaleFin.png");
    bg.transform.scale = glm::vec2(10000, 10000);
    bg.transform.layer = 3;

    unsigned int spriteIndex = 0;
    glm::vec2 start{}, end{1, 1};


    Umbra2D::Static rectangle;
    rectangle.setCollider(new Umbra2D::Colliders::Rectangle(1, 1));
    Umbra2D::Static sphere;
    sphere.setCollider(new Umbra2D::Colliders::Circle(1));
    Umbra2D::Static line;
    line.setCollider(new Umbra2D::Colliders::Line(1, glm::vec2(1, 1)));

    while (!w.shouldClose()) {
        w.startFrame();

        // code 
        lib->gui();

        // check out what this function does for more ImGui examples
        ImGui::ShowDemoWindow(); 
        
        c.UpdateProjMatrix(w);
        glm::mat4 proj, view;
        proj = c.getProj();
        view = c.getView();
        s.setMat4("view", &view);
        s.setMat4("proj", &proj);


        /*
        if (ImGui::TreeNode("bg")) {
            bg.gui();
            Umbra2D::Gui::showTexture(&bgtex);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("character")) {
            character.gui();
            float st[]{start.x, start.y}, e[]{end.x, end.y};
            if (ImGui::SliderFloat2("Start", st, 0, 1)) {
                start = glm::vec2(st[0], st[1]);
            }
            if (ImGui::SliderFloat2("End", e, 0, 1)) {
                end = glm::vec2(e[0], e[1]);
            }
            ImGui::SliderInt("SpriteIndex", (int*)&spriteIndex, 0, 100);
            Umbra2D::Gui::showTexture(ss.tex);
            ImGui::TreePop();
        }

        s.setVec2("start1", glm::vec2(0));
        s.setVec2("end1", glm::vec2(1));
        s.setTexture("texture1", bgtex.id, 0);
        bg.draw(&s);

        auto coords = ss.getSpriteCell(spriteIndex);
        start = coords.first;
        end = coords.second;
        
        s.setVec2("start1", start);
        s.setVec2("end1", end);
        s.setTexture("texture1", ss.tex->id, 0);
        character.draw(&s);
        */



        if (w.wasKeyPressed(GLFW_KEY_ESCAPE))
            break;
        
        float unitsPerFrame = 5;
        if (w.wasKeyPressed(GLFW_KEY_D))
            c.MoveHorizontally(-unitsPerFrame);
        if (w.wasKeyPressed(GLFW_KEY_A))
            c.MoveHorizontally(unitsPerFrame);
        if (w.wasKeyPressed(GLFW_KEY_W))
            c.MoveVertically(unitsPerFrame);
        if (w.wasKeyPressed(GLFW_KEY_S))
            c.MoveVertically(-unitsPerFrame);
        // code 

        w.endFrame();
    }

    delete lib;
    
    return 0;
}