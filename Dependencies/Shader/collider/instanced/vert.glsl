#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex;

uniform float depth[100];
uniform mat4 model[100];
uniform mat4 view;
uniform mat4 proj;

out vec2 Tex;

void main() {
    Tex = tex;
    gl_Position = proj * view * model[gl_InstanceID] * vec4(pos.xy, - 2 * (1 + depth[gl_InstanceID]), 1.);
}


