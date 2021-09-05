#pragma once

#include "Common.h"

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

            glm::vec<2, double> getSize();
    };
}
