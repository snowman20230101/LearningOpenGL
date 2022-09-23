#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    FragColor = mix(texture(texture1, vec2(TexCoord.s, 1.0f - TexCoord.t)), texture(texture2, vec2(TexCoord.s, 1.0f - TexCoord.t)), 0.2f);
}