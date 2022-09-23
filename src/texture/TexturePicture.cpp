//
// Created by windy on 2021/12/16.
// openGL 绘制纹理贴图 这里只用了一个纹理
// 纹理单元 glActiveTexture(GL_TEXTURE0) 激活纹理单元
// TODO 这里没有为对片段着色器中对 uniform sampler2D texture1; 变量赋值也可以显示，纹理采样对颜色。这是因为默认就是指定了一个默认对纹理单元。
//

#include "TexturePicture.h"

TexturePicture::TexturePicture() {
    printf("TexturePicture::TexturePicture()");
}

TexturePicture::~TexturePicture() {
    printf("TexturePicture::~TexturePicture()");
}

int TexturePicture::execute() {
    std::cout << "TexturePicture::execute()" << std::endl;

    createWindow();
    unsigned int programId = createGLProgram(textureVertexFileName, textureFragFileName1);

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertices), textureVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(textureIndices), textureIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr); // 顶点坐标
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float))); // 颜色
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float))); // 纹理坐标
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    // 纹理
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 纹理环绕方式
    // 1、GL_REPEAT: 对纹理的默认行为。重复纹理图像。
    // 2、GL_MIRRORED_REPEAT: 和GL_REPEAT一样，但每次重复图片是镜像放置的。
    // 3、GL_CLAMP_TO_EDGE:	纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。
    // 4、GL_CLAMP_TO_BORDER: 超出的坐标为用户指定的边缘颜色。
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    // 纹理过滤
    // 在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;

    std::string fileName = string(ROOT_DIR) + "resources/textures/container.jpg";
    unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        // 指定将生成mipmap的纹理对象绑定到的活动纹理单元的纹理目标。 必须是以下符号常量之一：GL_TEXTURE_2D或GL_TEXTURE_CUBE_MAP。
        // 错误
        //GL_INVALID_ENUM ：如果target不是GL_TEXTURE_2D或GL_TEXTURE_CUBE_MAP；
        //
        //GL_INVALID_OPERATION：如果纹理绑定的是立方体贴图，但是6个面却不共用统一的宽高格式和类型；
        //
        //GL_INVALID_OPERATION ：如果原图的宽高不是2^N。（纹理贴图没这个要求，但是如要生成mipmap组则要注意这个要求）
        //
        //GL_INVALID_OPERATION ：如果零级数组以压缩内部格式存储。
        glGenerateMipmap(GL_TEXTURE_2D); // glGenerateMipmap- 为纹理对象生成一组完整的mipmap
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    while (!glfwWindowShouldClose(pWindow)) {
        processInput(pWindow);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元，TODO 默认就是第一个纹理单元，如果是一个纹理采样，就可以不用写这个代码也行。
        glBindTexture(GL_TEXTURE_2D, texture);
        glUseProgram(programId);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(programId);

    glfwTerminate();

    return 0;
}