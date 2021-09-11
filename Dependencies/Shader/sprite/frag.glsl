#version 330 core

in vec2 Tex;

uniform sampler2D Texture;

uniform int pixelateLevel;

void main() {
    vec2 coords = Tex;
    if (pixelateLevel != 0)
        coords = floor(Tex * pixelateLevel) / pixelateLevel;
    vec4 color = texture(Texture, coords);
    if (color.a == 0)
        discard;
    gl_FragColor = color;
}
