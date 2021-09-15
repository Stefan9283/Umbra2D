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
}
```


## Umbra2D namespace

```C++
namespace Umbra2D {
    class Engine;

    class AssetLibrary;

    class Saver;
    class Loader;

    class FileExplorer;

    namespace Assets {
        class Animation;
        class Texture;
        class SpriteSheet;
    }

    class Camera;
    class Window;

    class Shader;
    class FrameBuffer;

    class Quad;
    class DynamicQuad;

    namespace Text {
       struct Character;
        class Font;
    }

    namespace Gui {
    }

    // TODO
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

    // TODO
    class Entity;
    class Static;
    class Dynamic;
}
```

## TODOs
#### Physics
* [ ] Collision Detection (+ Object Picker)
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
* [ ] Game Structure
* [ ] Rework on entities (component based)
* [ ] Game Objects (goal, player, enemy, prop)
#### Sound
* [ ] Sound Player
#### Misc
* [ ] Framecap
