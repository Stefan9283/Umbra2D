#pragma once

#include "Common.h"

/*
 * A simple camera object. 
 * It provides the projection and view matrices for the shading part 
 * of the engine pipeline.
 *
 * Can be moved in any direction using the MoveDIRECTION() funcs
*/
namespace Umbra2D {
    class Camera {
     private:
        glm::vec2 position{};
        glm::mat4 proj, view;
     public:
        Camera(Umbra2D::Window window);
        
        void UpdateProjMatrix(Umbra2D::Window window);
        void UpdateViewMatrix();
        
        glm::mat4 getView();
        glm::mat4 getProj();
        
        void MoveVertically(float units);
        void MoveHorizontally(float units);
    };
} 