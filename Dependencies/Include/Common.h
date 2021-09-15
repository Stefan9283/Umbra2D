#pragma once

/*
 *  add any
 *  - STL
 *  - external lib header reference
 *  - Umbra2D namespace object
 *  in this header
*/

#pragma region HEADERS

// C/C++ headers
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <filesystem>
#include <unordered_set>

// audio library
#include <portaudio.h>

// audio files parser
#include <sndfile.h>

// linear math
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

// scripting with C++ binding
#include <chaiscript/chaiscript.hpp>

// OpenGL funcs loader
#include <glad/glad.h>

// OpenGL context window + input
//#define GLFW_APIENTRY_DEFINED
#include <GLFW/glfw3.h>


// GUI library
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <misc/cpp/imgui_stdlib.h>

// ImGui Node API
#include <imgui_node_editor.h>

// images loader
#include <stb_image.h>


// ttf fonts loader
#include <ft2build.h>
#include FT_FREETYPE_H

#pragma endregion

#define ANIMATION Umbra2D::Assets::Animation
#define TEXTURE Umbra2D::Assets::Texture
#define SPRITE_SHEET Umbra2D::Assets::SpriteSheet

#define WINDOW umbra->getWindow()
#define LIBRARY umbra->getLibrary()

constexpr auto MAX_LEN = 1024;

namespace Umbra2D {
    class Engine;

    class AssetLibrary;

    class Saver;
    class Loader;

    class FileExplorer;

    class AudioPlayer;

    namespace Assets {
        class Animation;
        class Texture;
        class SpriteSheet;
    }

    class Camera;
    class Window;

    class Shader;
    class FrameBuffer;

    class Quad;         // for entities rendering
    class DynamicQuad; // for font rendering

    namespace Text {
       struct Character;
        class Font;
    }

    namespace Gui {
        class DragAndDropPayload;
    }

    namespace Colliders {
        class AbstractCollider;
        class Rectangle;
        class Circle;
        class Line;
    }

    // TODO
    namespace Physics {
        class AbstractEngine;
        class PlatformerEngine;
        class TopDownEngine;
    }

    // TODO
    namespace GameObjects {
        class Player;
        class NPC;
        class Prop;
        class Bullet;

        class Quest;
        class SubQuest;
    }

    class Entity;
    class Static;
    class Dynamic;
}
