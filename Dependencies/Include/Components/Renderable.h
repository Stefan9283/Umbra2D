#ifndef UMBRA2D_RENDERABLE_H
#define UMBRA2D_RENDERABLE_H

#include "Common.h"

namespace Umbra2D::Components::Renderables {
    class Renderable {

    };
    class Static : Renderable {
    private:
        TEXTURE* t = nullptr;
    public:
        void setTexture(std::string path, std::string name = "");
        void setTexture(TEXTURE* tex);
        void gui();
    };
    class Dynamic : Renderable {
    private:
        SPRITE_SHEET* ss = nullptr;
        int animationPlaying = -1;
        unsigned int currentSprite = 0;
        double time = 0;
        bool loopAnimation = false;
        float animationSpeed = 1;
    public:

        void setSpriteSheet(SPRITE_SHEET* ss);
        void setSpriteSheet(std::string pathToImage, glm::vec2 gridSize = glm::vec2(1),
                        unsigned int numOfSprites = 1, std::string name = "");
        void setAnimation(unsigned int animationID);
        void gui();
    };
}


#endif //UMBRA2D_RENDERABLE_H
