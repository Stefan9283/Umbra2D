#version 330 core
layout(location = 0) in vec4 vert;

uniform float depth;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 Tex;

void main() {
    Tex = vert.zw;
    gl_Position = proj * view * model * vec4(vert.xy, - 2 * (1 + depth), 1.);
}
