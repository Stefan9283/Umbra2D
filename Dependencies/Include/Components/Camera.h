#pragma once

#include "Common.h"
#include "Component.h"
/*
 * A simple camera object. 
 * It provides the projection and view matrices for the shading part 
 * of the engine pipeline.
 *
 * Can be moved in any direction using the MoveDIRECTION() funcs
*/
namespace Umbra2D::Components {
    class Camera : public Component {
     private:
        Umbra2D::Window* windowReference;
        glm::vec2 position{};
        glm::mat4 proj, view;
        float aspectRatio = 16/9.f;
        float nearZ = 0.f, farZ = 1001.f, scaleFactor = 1.f;
     public:
        Camera(Umbra2D::Window* window);

        void gui();


        void UpdateProjMatrix();
        void UpdateViewMatrix();
        
        glm::mat4 getView();
        glm::mat4 getProj();
        
        void MoveVertically(float units);
        void MoveHorizontally(float units);
        void Zoom(float zoom);

        // norm - normalized coords in the viewport space
        glm::vec2 getWorldCoords(glm::vec2 norm);
    };
} 