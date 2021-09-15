#pragma once

#include "Common.h"


/*
 *  Simple OpenGL context
 *  Is able to check if a key was either pressed or released via wasKeyACTION()
 *  For the all the available key check 
 *  the #defines in ./Dependencies/Vendor/glfw/include/GLFW/glfw3.h 
 *  or 
 *  https://www.glfw.org/docs/3.3/group__keys.html
 */
namespace Umbra2D {
    class Window {
        private:
        GLFWwindow* window;
        public:
            Window();
            ~Window();
            
            void startFrame();
            void endFrame();

            bool shouldClose();
            bool wasKeyPressed(int key);
            bool wasKeyReleased(int key);

            glm::vec2 getSize();
    };
}
