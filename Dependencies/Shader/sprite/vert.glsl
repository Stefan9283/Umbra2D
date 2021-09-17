#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex;

out vec2 Tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec2 start;
uniform vec2 end;

void main() {
    Tex = mix(start, end, tex);
    gl_Position = proj * view * model * vec4(pos.xy, 0, 1.);
}