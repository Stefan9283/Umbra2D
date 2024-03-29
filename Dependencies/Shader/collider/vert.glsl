#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 Tex;

void main() {
    Tex = tex;
    gl_Position = proj * view * model * vec4(pos.xy, - 2, 1.);
}


