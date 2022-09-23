#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D texture1;

void main() {
    // 由于图片因素，需要x轴旋转 vec2(1.0f - TexCoords.s, TexCoords.t)
    FragColor = texture(texture1, vec2(1.0f - TexCoords.s, TexCoords.t));
}
