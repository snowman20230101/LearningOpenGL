#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue;

void main() {
    vec2 y = vec2(TexCoord.s, 1.0f - TexCoord.t);
    FragColor = mix(texture(texture1, y), texture(texture2, y), mixValue);
}