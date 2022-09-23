#version 330 core
layout (location = 0) in vec3 vPos;// 顶点1

void main() {
    gl_Position = vec4(vPos.x, vPos.y, vPos.z, 1.0);
}
