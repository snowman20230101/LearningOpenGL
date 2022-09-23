#version 330 core
layout (location = 0) in vec3 vPos; // 顶点1
layout (location = 1) in vec3 vColor; // 顶点2

out vec3 vertColor; // 输出颜色，用于片元着色器中

void main() {
    gl_Position = vec4(vPos.x, vPos.y, vPos.z, 1.0);
    vertColor = vColor;
}
