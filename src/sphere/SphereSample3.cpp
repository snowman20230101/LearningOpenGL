//
// Created by windy on 2022/8/10.
// 球体绘制（第三种方式生成球体顶点）
// 生成了顶点坐标，纹理坐标，法线向量
//

#include "SphereSample3.h"
#include "Sphere.h"
#include <vector>

SphereSample3::SphereSample3() {
    std::cout << "SphereSample3::SphereSample3()" << std::endl;
}

SphereSample3::~SphereSample3() {
    std::cout << "SphereSample3::~SphereSample3()" << std::endl;
}

int SphereSample3::execute() {
    std::cout << "SphereSample3::execute()" << std::endl;

    createWindow();

    GLuint programId = createGLProgram(sphereSample3VertexFile, sphereSample3FragmentFile);

    Sphere mySphere(50);
    std::vector<int> ind = mySphere.getIndices(); // 球体点的标注
    std::vector<glm::vec3> vert = mySphere.getVertices(); // 球上的顶点
    std::vector<glm::vec2> tex = mySphere.getTexCoords(); // 纹理坐标
    std::vector<glm::vec3> norm = mySphere.getNormals(); // 球上法向量

    std::vector<float> sphereVertices; // 球体顶点

    int numIndices = mySphere.getNumIndices();
    for (int i = 0; i < numIndices; i++) {        // 把每一个点上的坐标（x,y,z），纹理坐标（s，t），法向量(a,b,c)存储进对应数组
        sphereVertices.push_back((vert[ind[i]]).x);
        sphereVertices.push_back((vert[ind[i]]).y);
        sphereVertices.push_back((vert[ind[i]]).z);
        sphereVertices.push_back((tex[ind[i]]).s);
        sphereVertices.push_back((tex[ind[i]]).t);
        sphereVertices.push_back((norm[ind[i]]).x);
        sphereVertices.push_back((norm[ind[i]]).y);
        sphereVertices.push_back((norm[ind[i]]).z);
    }

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(GLfloat), &sphereVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * sizeof(GLint), &ind[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (sizeof(GLfloat) * 3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (sizeof(GLfloat) * 5));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    std::string fileName = string(ROOT_DIR) + "resources/textures/earth.jpeg";
//    std::string fileName = string(ROOT_DIR) + "resources/textures/world_map_1.jpeg";
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
        glfwPollEvents();
        processInput(pWindow);

        glClearColor(0.0f, 0.34f, 0.57f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元，TODO 默认就是第一个纹理单元，如果是一个纹理采样，就可以不用写这个代码也行。
        glBindTexture(GL_TEXTURE_2D, texture);

        glUseProgram(programId);

        glm::mat4 model = glm::mat4(1.0);
        glm::mat4 view;
        glm::mat4 projection;
        // 旋转
        model = glm::rotate(model, (GLfloat) glfwGetTime() * glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.1f));

        // 位移
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.8f));

        // 投影矩阵
        projection = glm::perspective(glm::radians(270.0f), (GLfloat) SRC_WIDTH / (GLfloat) SRC_HEIGHT, 0.1f, 100.0f);

        glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1, GL_FALSE, glm::value_ptr(model));

        // 开启面剔除(只需要展示一个面，否则会有重合)
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glDepthFunc(GL_LEQUAL);
        glBindVertexArray(VAO);

        // 使用线框模式绘制
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPolygonMode(GL_FRONT_RIGHT, GL_LINE);
        // 锥体的三角形是逆时针的面认为是正方向
        glFrontFace(GL_CCW);
        glDrawArrays(GL_TRIANGLES, 0, numIndices);
//        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(pWindow);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture);
    glDeleteProgram(programId);

    glfwTerminate();
    return 0;
}