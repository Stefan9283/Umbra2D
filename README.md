# Umbra2D

### Save File Structure:

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


### Umbra2D namespace

```
namespace Umbra2D {
    class AssetLibrary;

    namespace Assets {
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
```



### TODO

* [ ] Framecap
* [-] Animation System (edit + getters)
* [ ] Save/Load Project System
* [ ] Collision Detection (+ Object Picker)
* [ ] Rigid Bodies
* [ ] Instanced Renderer with Viewport Culling
* [ ] Custom Font Rendering
* [ ] GUI Editor
* [ ] Game Objects (goal, player, enemy, prop)
* [ ] Game Graph
* [ ] Sound Player
