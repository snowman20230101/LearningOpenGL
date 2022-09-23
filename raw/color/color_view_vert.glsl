#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;

// we now define the uniform in the vertex shader and pass the 'view space' lightpos to the fragment shader. lightPos is currently in world space.
uniform vec3 lightPos;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    // 在观察空间中计算冯氏光照
    FragPos = vec3(view * model * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(view * model))) * aNormal;
    // Transform world-space light position to view-space light position
    LightPos = vec3(view * vec4(lightPos, 1.0));
}