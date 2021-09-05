#version 330 core

uniform vec4 color;

uniform bool circle;
uniform float radius;

out vec2 Tex;
uniform vec2 posoffset;

void main() {
    if (circle) {
        float l = length(posoffset - gl_FragPos);
        if (l > radius)
            gl_FragColor = vec4(0);    
        else gl_FragColor = color; 
    } else {
        gl_FragColor = color;
    }
}
