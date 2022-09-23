#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;

// 我们使用 GLSL 内建的 texture 函数来采样纹理的颜色，它第一个参数是纹理采样器，第二个参数是对应的纹理坐标。
// texture 函数会使用之前设置的纹理参数对相应的颜色值进行采样。这个片段着色器的输出就是纹理的（插值）纹理坐标上的(过滤后的)颜色。
void main() {
    // 直接返回纹理采样的颜色
    FragColor = texture(texture1, TexCoord);// 片元着色器返回的颜色是用纹理采样的纹理像素颜色
    //
//    FragColor = texture(texture1, vec2(TexCoord.s, TexCoord.t));

    // 特殊处理（纹理颜色与顶点颜色在片段着色器中相乘来混合二者的颜色）
//    FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0f);
}