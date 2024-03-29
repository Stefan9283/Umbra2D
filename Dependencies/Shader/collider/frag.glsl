#version 330 core

#define CIRCLE 0
#define RECTANGLE 1
#define LINE 2

uniform int shape;

uniform vec4 color;

in vec2 Tex;

void main() {
    switch (shape) {
        case 0: {
            float l = length(vec2(0.5, 0.5) - Tex);
            if (l > 0.5)
                discard;
            else if (l > 0.45)
                gl_FragColor = vec4(vec3(0.3), 1) * color;
            else
                gl_FragColor = color;
            break;
        }
        case 1: {
            if (Tex.x < 0.05 || Tex.x > 0.95 || Tex.y < 0.05 || Tex.y > 0.95)
                gl_FragColor = vec4(vec3(0.3), 1) * color;
            else
                gl_FragColor = color;
            break;
        }
        case 2: {
            gl_FragColor = vec4(vec3(0.3), 1) * color;
        }
    }
}
