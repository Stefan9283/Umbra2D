#version 330 core

in vec2 Tex;

uniform sampler2D Texture;

uniform int pixelateLevel;

void main() {
    vec2 coords = Tex;
    if (pixelateLevel != 0)
        coords = floor(Tex * pixelateLevel) / pixelateLevel;

    gl_FragColor = texture(Texture, coords);
}
