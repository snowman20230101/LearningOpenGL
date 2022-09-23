//
// Created by windy on 2022/8/5.
//

#include "BeatingHeartSample.h"


#define MATH_PI 3.1415926535897932384626433832802

BeatingHeartSample::BeatingHeartSample() {
    printf("");
}

BeatingHeartSample::~BeatingHeartSample() {
    printf("");
}

int BeatingHeartSample::execute() {
    std::cout << "BeatingHeartSample execute()" << std::endl;
    createWindow();

    // TODO 1、创建着色器程序
    GLuint programId = createGLProgram(beatingHeartVertexFile, beatingHeartFragmentFile);

    unsigned int VAO;
    unsigned int VBOs[3];

    // TODO 2、创建一个顶点数组对象 VAO 对象 其实叫申请内存
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // TODO 3、创建一个顶点缓冲对象。 VBO 对象 其实叫申请内存
    // 顶点坐标
    glGenBuffers(3, VBOs);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCoords), verticesCoords, GL_STATIC_DRAW);

    // 纹理坐标
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // TODO 4、设置顶点属性指针，glVertexAttribPointer()函数告诉OpenGL该如何解析顶点数据
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (const void *) 0);

    // TODO 5、创建 RGBA texture
    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    // TODO 6、解绑
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
    glBindVertexArray(GL_NONE);

    while (!glfwWindowShouldClose(pWindow)) {
        processInput(pWindow);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        updateMVPMatrix(m_MVPMatrix, m_AngleX, m_AngleY, (float) SRC_WIDTH / SRC_HEIGHT);

        glUseProgram(programId);

        glBindVertexArray(VAO);

        glUniformMatrix4fv(m_MVPMatLoc, 1, GL_FALSE, &m_MVPMatrix[0][0]);
        float time = static_cast<float>(fmod(glfwGetTime(), 2000) / 2000);
        glUniform1f(m_TimeLoc, time);
        glUniform2f(m_SizeLoc, SRC_WIDTH, SRC_HEIGHT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const void *) 0);
        glBindVertexArray(0);

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glDeleteTextures(1, &textureId);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(3, VBOs);
    glDeleteProgram(programId);

    glfwTerminate();

    return 0;
}

void BeatingHeartSample::updateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY, float ratio) {
    angleX = angleX % 360;
    angleY = angleY % 360;

    //转化为弧度角
    float radiansX = static_cast<float>(MATH_PI / 180.0f * angleX);
    float radiansY = static_cast<float>(MATH_PI / 180.0f * angleY);

    // Projection matrix
    glm::mat4 Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    // glm::mat4 Projection = glm::frustum(-ratio, ratio, -1.0f, 1.0f, 4.0f, 100.0f);
    // glm::mat4 Projection = glm::perspective(45.0f,ratio, 0.1f,100.f);

    // View matrix
    glm::mat4 View = glm::lookAt(
            glm::vec3(0, 0, 4), // Camera is at (0,0,1), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix
    glm::mat4 Model = glm::mat4(1.0f);
    Model = glm::scale(Model, glm::vec3(m_ScaleX, m_ScaleY, 1.0f));
    Model = glm::rotate(Model, radiansX, glm::vec3(1.0f, 0.0f, 0.0f));
    Model = glm::rotate(Model, radiansY, glm::vec3(0.0f, 1.0f, 0.0f));
    Model = glm::translate(Model, glm::vec3(0.0f, 0.0f, 0.0f));

    mvpMatrix = Projection * View * Model;
}