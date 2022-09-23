#version 330 core
precision mediump float;
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D text;
uniform vec3 textColor;

void main() {
    vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(text, TexCoords).r);
    FragColor = vec4(textColor, 1.0f) * sampled;
}
