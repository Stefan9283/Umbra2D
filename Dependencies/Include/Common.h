#pragma once

/*
 *  add any STL or external lib header reference here  
*/

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <misc/cpp/imgui_stdlib.h>

//#include <ft2build.h>
//#include FT_FREETYPE_H

#include <stb_image.h>

#include <GLFW/glfw3.h>

#include <cstdlib>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>

#define ANIMATION Umbra2D::Assets::Animation
#define TEXTURE Umbra2D::Assets::Texture
#define SPRITE_SHEET Umbra2D::Assets::SpriteSheet

namespace Umbra2D {
    class AssetLibrary;

    class Saver;
    class Loader;

    namespace Assets {
        class Animation;
        class Texture;    
        class SpriteSheet;
    }    

    class Camera;
    class Window;
    class Shader;
    class Quad;

    namespace Colliders {
        class AbstractCollider;
        class Rectangle;
        class Circle;
        class Line;
    }

    // entity types
    class Entity;
    class Static;
    class Dynamic;
}