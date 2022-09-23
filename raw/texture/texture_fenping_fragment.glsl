#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;

const float horizontal = 2.0;
const float vertical = 2.0;

void main() {
    // 参数控制，分屏必须是1个以上的屏幕
    float horizontalCount = max(horizontal, 1.0);
    float verticalCount = max(vertical, 1.0);

    float ratio = verticalCount / horizontalCount;
    vec2 originSize = vec2(1.0, 1.0);
    vec2 newSize = originSize;
    if (ratio > 1.0) {
        newSize.y = 1.0 / ratio;
    } else {
        newSize.x = ratio;
    }
    // 计算新的图像在原始图像中的偏移量。因为我们的图像要居中裁剪，所以要计算出裁剪后的偏移。比如 (2.0 / 3.0, 1.0) 的图像，对应的 offset 是 (1.0 / 6.0, 0.0)
    vec2 offset = (originSize - newSize) / 2.0;
    // 将原始的纹理坐标，乘上 horizontalCount 和 verticalCount 的较小者，然后对新的尺寸进行求模运算。
    vec2 position = offset + mod(TexCoord * min(horizontalCount, verticalCount), newSize);
    // 通过新的计算出来的纹理坐标，从纹理中读出相应的颜色值输出。
    //    FragColor = texture(texture1, position);

    vec4 vCameraColor = texture(texture1, TexCoord);
    // 黑白滤镜
    float fGrayColor = (0.299 * vCameraColor.r + 0.587 * vCameraColor.g + 0.114 * vCameraColor.b);
//    FragColor = vec4(fGrayColor, fGrayColor, fGrayColor, 1.0);
    FragColor = vCameraColor;
}