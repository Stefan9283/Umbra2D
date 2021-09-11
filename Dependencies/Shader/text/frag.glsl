#version 330 core

uniform vec4 color;

uniform sampler2D Texture;
in vec2 Tex;

void main() {

    float texColor = texture(Texture, Tex).r;
    if (texColor == 0)
        discard;
    gl_FragColor = vec4(vec3(1), texColor) * color;
}
