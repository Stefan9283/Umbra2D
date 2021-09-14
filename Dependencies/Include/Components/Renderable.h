#ifndef UMBRA2D_RENDERABLE_H
#define UMBRA2D_RENDERABLE_H

#include "Common.h"
#include "Component.h"

namespace Umbra2D::Components::Renderables {
    class Static : public COMPONENT {
    private:
        TEXTURE* t = nullptr;
    public:
        void setTexture(std::string path, std::string name = "");
        void setTexture(TEXTURE* tex);
        void gui() override;
    };
    class Dynamic : public COMPONENT {
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
        void gui() override;
    };
}


#endif //UMBRA2D_RENDERABLE_H
