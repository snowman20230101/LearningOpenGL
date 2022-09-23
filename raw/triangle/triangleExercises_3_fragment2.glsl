#version 330 core

out vec4 fragColor;// 输出，用于片元着色器输出
uniform vec4 ourColor;

void main() {
    fragColor = ourColor;
}