//
// Created by windy on 2021/12/17.
// GLM 数学运算，位移，旋转，缩放，基础运算。
//

#include "GLMSample.h"

float mixValueTmp = 0.2f;

void key_callback_glm(GLFWwindow *window, int key, int scancode, int action, int mode);

GLMSample::GLMSample() {
    std::cout << "" << std::endl;
    mixValueTmp = mMixValue;
}

GLMSample::~GLMSample() {
    std::cout << "" << std::endl;
}

int GLMSample::execute() {
    std::cout << "GLMSample::execute()" << std::endl;

    // Test GLM
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z << std::endl; // (2.0, 1.0, 0.0)

    createWindow();

    glfwSetKeyCallback(pWindow, key_callback_glm);
    unsigned int programId = createGLProgram(glmVertexFileName, glmFragmentFileName);

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    // 纹理
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;

    std::string fileName = string(ROOT_DIR) + "resources/textures/container.jpg";
    unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture1" << std::endl;
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    // texture2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::string fileName2 = string(ROOT_DIR) + "resources/textures/awesomeface.png";
    data = stbi_load(fileName2.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture2" << std::endl;
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    while (!glfwWindowShouldClose(pWindow)) {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        processInput(pWindow);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programId);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform1i(glGetUniformLocation(programId, "texture1"), 0);
        glUniform1i(glGetUniformLocation(programId, "texture2"), 1);
        glUniform1f(glGetUniformLocation(programId, "mixValue"), mixValueTmp);

        GLint transformLoc = glGetUniformLocation(programId, "transform");

        // 创建单位矩阵 TODO（单位矩阵是一个除了对角线以外都是0的N×N矩阵）  make sure to initialize matrix to identity matrix first
        glm::mat4 trans = glm::mat4(1.0f);

        // Test 1
//        trans = glm::rotate(trans, glm::radians(0.f), glm::vec3(0.0, 0.0, 1.0)); // 旋转 逆时针90
//        trans = glm::scale(trans, glm::vec3(0.7f, 0.7f, 1.0f)); // 缩放 0.5倍 由于2D平面Z轴可以随意一个值。

        // Test 2
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 1.0f)); // 变换矩阵 位移
        trans = glm::rotate(trans, glm::radians((float) glfwGetTime() * 90.f), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 1.0f));

        // Test 3
        // 使用应用在箱子上的最后一个变换，尝试将其改变为先旋转，后位移。看看发生了什么，试着想想为什么会发生这样的事情
        // 上面的，位移和旋转
//        trans = glm::rotate(trans, glm::radians((float) glfwGetTime() * 90.f), glm::vec3(0.0f, 0.0f, 1.0f));
//        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 1.0f)); // 变换矩阵 位移
//        trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 1.0f));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 尝试再次调用glDrawElements画出第二个箱子，只使用变换将其摆放在不同的位置。让这个箱子被摆放在窗口的左上角，并且会不断的缩放（而不是旋转）。
        // sin函数在这里会很有用，不过注意使用sin函数时应用负值会导致物体被翻转
        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        GLfloat scaleAmount = (GLfloat) sin(glfwGetTime());
        trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, 1.0f));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(pWindow);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

void key_callback_glm(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        mixValueTmp += 0.1f;
        if (mixValueTmp >= 1.0f)
            mixValueTmp = 1.0f;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        mixValueTmp -= 0.1f;
        if (mixValueTmp <= 0.0f)
            mixValueTmp = 0.0f;
    }

    printf("mixValueTmp=%f\n", mixValueTmp);
}