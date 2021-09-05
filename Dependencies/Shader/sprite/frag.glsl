#version 330 core

in vec2 Tex1;
in vec2 Tex2;

uniform float bias;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform int pixelateLevel;

void main() {
    vec4 color;
    
    if (bias < 0.5) {
        vec2 Tex = Tex1;
        if (pixelateLevel != 0)
            Tex = floor(Tex1 * pixelateLevel) / pixelateLevel;
        color = texture(texture1, Tex);
    }
    else
        color = texture(texture2, Tex2);

    gl_FragColor = color;
}
