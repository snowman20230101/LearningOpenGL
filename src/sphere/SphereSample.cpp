//
// Created by windy on 2022/8/10.
// 绘制球体
//

#include "SphereSample.h"

#include <vector>

const GLfloat PI = 3.14159265358979323846f;
// 将球横纵划分成50*50的网格
const int Y_SEGMENTS = 50;
const int X_SEGMENTS = 50;


SphereSample::SphereSample() {
    std::cout << "SphereSample::SphereSample()" << std::endl;
}

SphereSample::~SphereSample() {
    std::cout << "SphereSample::~SphereSample()" << std::endl;
}

int SphereSample::execute() {
    std::cout << "SphereSample::execute()" << std::endl;

    createWindow();

    GLuint programId = createGLProgram(sphereSampleVertexFile, sphereSampleFragmentFile);
//    GLuint programId = createGLProgram(sphereLightSampleVertexFile1, sphereLightSampleFragmentFile1);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    std::vector<float> sphereVertices; // 球体顶点
    std::vector<int> sphereIndices; // 球体坐标系

    // 生成球体顶点数据
    for (int y = 0; y < Y_SEGMENTS; ++y) {
        for (int x = 0; x < X_SEGMENTS; ++x) {
            float xSegment = (float) x / (float) X_SEGMENTS;
            float ySegment = (float) y / (float) Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            sphereVertices.push_back(xPos);
            sphereVertices.push_back(yPos);
            sphereVertices.push_back(zPos);
        }
    }

    // 生成球的 Indices 数据
    for (int i = 0; i < Y_SEGMENTS; i++) {
        for (int j = 0; j < X_SEGMENTS; j++) {
            sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
            sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
            sphereIndices.push_back(i * (X_SEGMENTS + 1) + j + 1);
        }
    }

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(GLfloat), &sphereVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(GLint), &sphereIndices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(pWindow)) {
        glfwPollEvents();
        processInput(pWindow);

        glClearColor(0.0f, 0.34f, 0.57f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programId);
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
        // 旋转
        model = glm::rotate(model, (GLfloat) glfwGetTime() * glm::radians(30.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        // 位移
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));

        // 投影矩阵
        projection = glm::perspective(glm::radians(45.0f), (GLfloat) SRC_WIDTH / (GLfloat) SRC_HEIGHT, 0.1f, 100.0f);

        glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1, GL_FALSE, glm::value_ptr(model));

        // 开启面剔除(只需要展示一个面，否则会有重合)
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);

        glBindVertexArray(VAO);
        // 使用线框模式绘制
        glPolygonMode(GL_FRONT_RIGHT, GL_LINE);
        glDrawElements(GL_TRIANGLE_STRIP, X_SEGMENTS * Y_SEGMENTS * 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(pWindow);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(programId);

    glfwTerminate();
    return 0;
}




