#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue;

void main() {
    // linearly interpolate between both textures (80% container, 20% awesomeface)
    vec2 turnCoord = vec2(TexCoord.s, 1.0f - TexCoord.t);
    FragColor = mix(texture(texture1, turnCoord), texture(texture2, turnCoord), 0.2);
}