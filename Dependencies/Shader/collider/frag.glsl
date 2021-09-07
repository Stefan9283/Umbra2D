#version 330 core

uniform bool circle;
uniform float radius;
uniform vec4 color;

in vec2 Tex;

void main() {
    if (circle) {
        float l = length(vec2(0.5, 0.5) - Tex);
        if (l > 0.5)
            discard;
        else if (l > 0.45)
            gl_FragColor = vec4(vec3(0.3), 1) * color;
        else
            gl_FragColor = color;
    } else {
        gl_FragColor = color;
    }
}
