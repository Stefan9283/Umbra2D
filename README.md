# Umbra2D

## Save File Structure:

```
AssetLibrary {
    [] Texture {
        str name, path
    }

    [] SpriteSheet {
        int SpritesNo 
        ivec2 gridSize // the distribution of frames in the sprite sheet
                      // gridSize.x = num of columns | gridSize.y = num of rows
        Texture {
            str name, path
        }
        [] Animation {
            str name
            [] Keyframes {
                int index
                float timeUntilNextFrame
            }
        }
        [] str FrameDescriptions  // each of the SpriteNo frames 
                                 // has a brief description/name
                                // (it can be an empty string)
    }

    [] Shaders {
        nane, pathToVertexShader, pathToFragmentShader
    }
}
```


## Umbra2D namespace

```C++
namespace Umbra2D {
   class Umbra2DEngine;

   class Window;
   class Scene;
   class AssetLibrary;

   namespace IO {
       class Saver;
       class Loader;
   }
   namespace Audio {
       class AudioPlayer;
       class myFileHandler;
   }
   namespace Assets {
       class Animation;
       class Texture;
       class SpriteSheet;
   }

   

   class Renderer; // TODO

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
   
   namespace Physics { // TODO
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
```

## TODOs
#### Physics
* [x] Collision Detection
* [ ] Object Picker
* [ ] Rigid Bodies
* [ ] Platformer Physics Engine
* [ ] TopDown RPG-Style Physics Engine
#### Graphics
* [x] Animation System (edit + getters)
* [x] Custom Font Rendering
* [ ] Instanced Renderer 
* [ ] Viewport Culling
* [ ] Post-Processing
#### Tools
* [x] Save/Load Project System
* [ ] GUI Editor
* [ ] Game Graph
#### Game 
* [x] Rework on entities (component based)
* [ ] Game Structure
* [ ] Game Objects (goal, player, enemy, prop)
#### Sound
* [x] Sound Player
#### Misc
* [ ] Framecap
