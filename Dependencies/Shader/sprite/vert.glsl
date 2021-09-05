#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex;

out vec2 Tex1;
out vec2 Tex2;

uniform float depth;

uniform vec2 posoffset;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec2 start1;
uniform vec2 end1;
uniform vec2 start2;
uniform vec2 end2;

void main() {
    
    Tex1 = mix(start1, end1, tex); // (tex + start1) * (end1 - start1);
    Tex2 = (tex + start2) * (end2 - start2);
    gl_Position = proj * view * model * vec4(pos.xy + posoffset, - (0.1 + depth), 1.);
}