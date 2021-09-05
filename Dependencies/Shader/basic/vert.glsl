#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex;

uniform float depth;

uniform vec2 posoffset;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj * view * model * vec4(pos.xy + posoffset, - (0.1 + depth), 1.);
}