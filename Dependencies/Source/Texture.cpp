#include "Texture.h"
#include "Gui.h"

namespace Umbra2D::Assets {
    Texture::Texture(std::string path, std::string name) {
        auto r = loadFromFile(path);
        this->id = r.first;
        this->resolution = r.second;
        this->path = path;
        if (name.size())
            this->name = name;
        else 
            this->name = path;
    }
    void Texture::gui() {
        ImGui::Text(
                ("name: " + name + "\n" +
                 "path: " + path + "\n" +
                 "resolution: " + std::to_string(resolution.x) + "x" + std::to_string(resolution.y) + "\n").c_str());
        Umbra2D::Gui::showTexture(this);
    }
    Texture::~Texture() {
        glDeleteTextures(1, (GLuint*)&this->id);
    }
    int Texture::getID() { return id; }
    std::string Texture::getPath() { return path; }
    glm::ivec2 Texture::getResolution() { return resolution; }
    
    std::pair<int, glm::vec2> Texture::loadFromFile(std::string path) {
        if (!std::filesystem::exists(path)) {
            std::string current = std::filesystem::current_path().string();
            std::replace(current.begin(), current.end(), '\\', '/');
            std::cout << "File " << current << '/' << path << " doesn't exist\n";
            return {-1, {}};
        }
        // load and create a texture
        // -------------------------
        unsigned int texture;
        // ---------
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

    SpriteSheet::SpriteSheet(std::string pathToImage, glm::vec2 gridSize, unsigned int numOfSprites, std::string name) {
        this->gridSize = gridSize;
        this->numOfSprites = numOfSprites;
        tex = new Texture(pathToImage);
        frameDescriptions.reserve(numOfSprites);
    }
    void SpriteSheet::gui() {
        this->tex->gui();
    }
    void SpriteSheet::addSpriteDescription(std::string name, unsigned int index) {
        frameDescriptions[index] = name;
    } // TODO
    std::pair<glm::vec2, glm::vec2> SpriteSheet::getSpriteCell(unsigned int index) {
        glm::vec2 spriteDimension = glm::vec2(1.) / (glm::vec2)gridSize;

        index = index %  numOfSprites;

        glm::vec2 start = { (index % gridSize.x) * spriteDimension.x, 1 - (int)(index / gridSize.x + 1) * spriteDimension.y};

        return 
        {
            start,
            start + spriteDimension
        };
    }

}
