#version 330 core
out vec4 FragColor;

uniform sampler2D texture1;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;// 光源位置
uniform vec3 viewPos;// 具体物体世界空间位置

uniform vec3 lightColor;// 光源颜色
uniform vec3 objectColor;// 具体的物体颜色

void main() {
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

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = texture(texture1, TexCoords) * vec4(result, 1.0f);
}