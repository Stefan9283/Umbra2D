#include "Texture.h"

namespace Umbra2D {
    Texture::Texture(std::string name, std::string path, int id, glm::vec2 resolution) {
        this->name = name;
        this->id = id;
        this->path = path;
        this->resolution = resolution;
    }
    Texture::Texture(std::string path) {
        *this = this->loadFromFile(path);
    }
    Texture::Texture() {
        name = "";
        path = "";
        id = -1;
        resolution = glm::vec2(0);
    }
    
    void destroy() {} // TODO
    Texture Texture::loadFromFile(std::string path) {
        if (!std::filesystem::exists(path)) {
            std::cout << "File " << path << " doesn't exist\n";
            return {};
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
        return {path, path, (int)texture, {width, height}};
    }


    SpriteSheet::SpriteSheet(std::string pathToImage, glm::vec2 gridSize, unsigned int numOfSprites) {
        this->gridSize = gridSize;
        this->numOfSprites = numOfSprites;
        tex = Texture::loadFromFile(pathToImage);
    }
    void SpriteSheet::addSpriteDescription(std::string name, unsigned int index) {
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
