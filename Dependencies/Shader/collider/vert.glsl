#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex;

uniform float depth;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 Tex;

void main() {
    Tex = tex;
    gl_Position = proj * view * model * vec4(pos.xy, - (0.1 + depth), 1.);
}


