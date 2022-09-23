#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue;

void main() {
    // 这个是什么操作
    vec2 y = vec2(TexCoord.s, 1.0f - TexCoord.t);
    // mix 线性内插 TODO mix(x,y,a)  a控制混合结果 return x(1-a) +y*a  返回 线性混合的值
    FragColor = mix(texture(texture1, y), texture(texture2, y), mixValue);
}