# Umbra2D

### Save File Structure:

```
AssetLibrary {
    [] Texture {
        str name, path
    }

    [] SpriteSheet {
        int SpritesNo 
        ivec2 gridSize 
        Texture t
        [] Animation {
            str name
            [] Keyframes {
                int index
                float timeUntilNextFrame
            }
        }
    }
}
```

### TODO

* [ ] Framecap
* [ ] Animation System (edit + getters)
* [ ] Save/Load Project System
* [ ] Collision Detection (+ Object Picker)
* [ ] Rigid Bodies
* [ ] Instanced Renderer with Viewport Culling
* [ ] Custom Font Rendering
* [ ] GUI Editor
* [ ] Game Objects (goal, player, enemy, prop)
* [ ] Game Graph
