#version 330 core

in vec3 vertColor;// 输入（来自顶点着色器）
out vec3 fragColor;// 输出，用于片元着色器输出

void main() {
    fragColor = vertColor;
}

//void mainImage(out vec4 fragColor, in vec2 fragCoord){
//    //纹理坐标  (0 ~ 1)
//    vec2 uv = fragCoord / iResolution.xy;
//    // fragColor = vec4(uv.x,0.,0.,1.0); //沿X轴方向的颜色渐变  黑到红
//    fragColor = vec4(uv.y, 0., 0., 1.);//沿Y轴方向的颜色渐变  黑到红
//}