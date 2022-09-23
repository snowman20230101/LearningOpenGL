
/*
早期的光照着色器，开发者在顶点着色器中实现冯氏光照。
在顶点着色器中做这件事的优势是，相比片段来说，顶点要少得多，因此会更高效，所以(开销大的)光照计算频率会更低。
然而，顶点着色器中的颜色值是只是顶点的颜色值，片段的颜色值是它与周围的颜色值的插值。
结果就是这种光照看起来不会非常真实，除非使用了大量顶点。

在顶点着色器中实现的冯氏光照模型叫做Gouraud着色，而不是冯氏着色。
记住由于插值，这种光照连起来有点逊色。冯氏着色能产生更平滑的光照效果。
*/
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 LightingColor;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    vec3 FragPos = vec3(model * vec4(aPos, 1.0f));// 在世界空间中的顶点位置
    vec3 Normal = mat3(transpose(inverse(model))) * aNormal;

    // 环境光照 Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // 漫反射光照 Diffuse
    vec3 norm = normalize(Normal);
    // 计算光源和片段位置之间的方向向量
    vec3 lightDir = normalize(lightPos - FragPos);// 光的方向向量
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // 镜面光照
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    vec3 result = (ambient + diffuse + specular);

    LightingColor = result;
}