#pragma once

/*
 *  add any
 *  - STL
 *  - external lib header reference
 *  - Umbra2D namespace object
 *  in this header
*/
#pragma region HEADERS

// disable any warning coming from an external library
#pragma warning(push, 0)

// GUI library
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <misc/cpp/imgui_stdlib.h>

// ECS lib
#include <entt/entt.hpp>

#include <memplumber.h>
#define new new(__FILE__, __LINE__)

// C/C++ headers
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
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
// for projection i.e. glm::closestPointOnLine()
#include <glm/gtx/closest_point.hpp>

// scripting with C++ binding
#include <chaiscript/chaiscript.hpp>

// OpenGL funcs loader
#include <glad/glad.h>

// OpenGL context window + input
//#define GLFW_APIENTRY_DEFINED
#include <GLFW/glfw3.h>


// ImGui Node API
#include <imnodes.h>

// images loader
#include <stb_image.h>

// ttf fonts loader
#include <ft2build.h>
#include FT_FREETYPE_H



#pragma warning(pop)

#pragma endregion


//#define NO_IMGUI

#define ANIMATION Umbra2D::Assets::Animation
#define TEXTURE Umbra2D::Assets::Texture
#define SPRITE_SHEET Umbra2D::Assets::SpriteSheet
#define SHADER Umbra2D::Graphics::Shader

#define WINDOW umbra->getWindow()
#define LIBRARY umbra->getLibrary()

#define COMPONENT Umbra2D::Components::Component

#define CAMERA Umbra2D::Components::Camera

#define COLLIDER Umbra2D::Components::Colliders::AbstractCollider
#define RECTANGLE Umbra2D::Components::Colliders::Rectangle
#define AARECTANGLE Umbra2D::Components::Colliders::AARectangle
#define CIRCLE Umbra2D::Components::Colliders::Circle
#define LINE Umbra2D::Components::Colliders::Line

#define RENDERABLE Umbra2D::Components::Renderables::Renderable
#define STATIC Umbra2D::Components::Renderables::Static
#define DYNAMIC Umbra2D::Components::Renderables::Dynamic

#define TRANSFORM Umbra2D::Components::Transform

constexpr auto MAX_LEN = 1024;

namespace Umbra2D {
    class Umbra2DEngine;

    class Window;
    class Scene;
    class AssetLibrary;

    namespace IO {
        class Saver;
        class Loader;
    }

    namespace Assets {
        class Animation;
        class Texture;
        class SpriteSheet;
    }

    namespace Graphics {
        class Shader;
        class FrameBuffer;
        class GraphicsPipeline;
        class RenderPass;
        class Quad;         // for entities rendering
        class DynamicQuad; // for font rendering
    }
    namespace Gui {
        class ImGuiTheme;
        class FileExplorer;
        class Editor;
    }
    namespace Text {
       struct Character;
        class Font;
    }

    // TODO
    class Renderer;
    // TODO
    namespace Physics {
        class RigidBody;
        namespace System {
            class AbstractEngine;
            class PlatformerEngine;
            class TopDownEngine;
        }
    }


    class Entity;

    namespace Components {
        class Component;
        class Transform;
        class Camera;
        namespace Colliders {
            class AbstractCollider;
            class Rectangle;
            class AARectangle;
            class Circle;
            class Line;
        }
        namespace Renderables {
            class Renderable;
            class Static;
            class Dynamic;
        }
    }
}

