#include "Texture.h"
#include "Gui.h"

namespace Umbra2D::Assets {

    int Animation::getBestFrameInterval(float time) {
        int index = 0;
        float timeUntilNow = 0;
        for (auto const& frame : frames)
            if (frame.second + timeUntilNow > time)
                break;
            else {
                index++;
                timeUntilNow += frame.second;
            }

        index = index ? frames.size() - 1 : index < frames.size() - 1;

        return frames[index].first;
    }
    float Animation::getTotalDuration() {
        float total = 0;
        for (auto frame : frames)
            total += frame.second;
        return total;
    }

    // Texture
    Texture::Texture(unsigned int id, glm::ivec2 resolution, std::string name) {
        this->name = name;
        this->id = id;
        this->resolution = resolution;
        this->path = "NONE";
    }
    Texture::Texture(std::string path, std::string name) {
        auto r = loadFromFile(path);
        this->id = r.first;
        this->resolution = r.second;
        this->path = path;
        if (!name.empty())
            this->name = name;
        else 
            this->name = path;
    }
    Texture::~Texture() { glDeleteTextures(1, (GLuint*)&id); }

    void Texture::gui() {
        ImGui::Text(
                "name: %s\npath: %s\nresolution: %dx%d", name.c_str(), path.c_str(), resolution.x, resolution.y);
        Umbra2D::Gui::showTexture(this);
    }

    std::pair<int, glm::vec2> Texture::loadFromFile(std::string path) {
        if (!std::filesystem::exists(path)) {
            std::string current = std::filesystem::current_path().string();
            std::replace(current.begin(), current.end(), '\\', '/');
            std::cout << "File " << current << '/' << path << " doesn't exist\n";
            return {0, {}};
        }
        // load and create a texture
        // -------------------------
        unsigned int texture;
        // ---------
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // set the texture wrapping parameters
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

        if (data) {
            switch (nrChannels) {
                case 4:
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                    break;
                case 3:
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    break;
                case 2:
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, data);
                    break;
                case 1:
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
                    break;
            }
            glGenerateMipmap(GL_TEXTURE_2D);

        } else {
            throw std::runtime_error("Failed to load texture");
        }
        stbi_image_free(data);
        return {(int)texture, {width, height}};
    }

    int Texture::getID() { return id; }
    std::string Texture::getPath() { return path; }
    glm::ivec2 Texture::getResolution() { return resolution; }
    

    // SpriteSheet
    SpriteSheet::SpriteSheet(std::string pathToImage, glm::vec2 gridSize, unsigned int numOfSprites, std::string name) {
        this->gridSize = gridSize;
        this->numOfSprites = numOfSprites;
        tex = new Texture(pathToImage, name);
        frameDescriptions.resize(numOfSprites);
    }
    SpriteSheet::~SpriteSheet() { delete tex; }

    void SpriteSheet::gui() {
        this->tex->gui();
        for (const auto& anim : animations) {
            if (ImGui::TreeNode(anim.name.c_str())) {
                for (auto sprite : anim.frames) {
                    auto corners = getSpriteCell(sprite.first);
                    Umbra2D::Gui::showTexture(tex, corners.first, corners.second);
                    ImGui::Text("FrameName: %s\nFrameID: %d\nTimeUntilNextFrame: %f\n",
                            frameDescriptions[sprite.first].c_str(), sprite.first, sprite.second);
                }
                ImGui::TreePop();
            }
        }

    }

    void SpriteSheet::addSpriteDescription(std::string name, unsigned int index) {
        frameDescriptions[index] = name;
    }
    void SpriteSheet::addAnimation(Animation anim) {
        this->animations.push_back(anim);
        animationsCount++;
    }

    std::pair<glm::vec2, glm::vec2> SpriteSheet::getSpriteCell(unsigned int index) {
        glm::vec2 spriteDimension = glm::vec2(1.) / (glm::vec2)gridSize;

        index = index %  numOfSprites;

        glm::vec2 start = { (index % gridSize.x) * spriteDimension.x, 1 - (index / gridSize.x + 1) * spriteDimension.y};

        return 
        {
            start,
            start + spriteDimension
        };
    }

    std::vector<Animation> SpriteSheet::getAnimations() {
        return animations;
    }
    Animation& SpriteSheet::getAnimation(unsigned int index) {
        return animations[index];
    }
    unsigned int SpriteSheet::getAnimationsCount() { return animationsCount; }


    std::vector<std::string> SpriteSheet::getFrameDescriptions() {
        return frameDescriptions;
    }
    glm::vec3 SpriteSheet::getSize() {
        return glm::vec3(numOfSprites, gridSize);
    }
}
