//
// Created by windy on 2021/12/21.
// 光照基础
// 2、尝试使用不同的环境光、散射镜面强度，观察光照效果。改变镜面光照的shininess因子试试。？？？ 没做
//

#include "GLColor.h"

// Light attributes
glm::vec3 colorLightPos(1.2f, 1.0f, 2.0f);

GLColor::GLColor() {
    std::cout << "GLColor::GLColor()" << std::endl;
}

GLColor::~GLColor() {
    std::cout << "GLColor::~GLColor()" << std::endl;
}

int GLColor::execute() {
    std::cout << "GLColor::execute()" << std::endl;

    createWindow();

    glfwSetScrollCallback(pWindow, scrollCallback);
    glfwSetCursorPosCallback(pWindow, mouseCallback);

//    GLuint programId = createGLProgram(colorVertFile, colorFragFile);
    // 3、在观察空间(而不是世界空间)中计算冯氏光照。
//    GLuint programId = createGLProgram(colorViewVertFile, colorViewFragFile);
    // 4、尝试实现一个Gouraud光照来模拟冯氏光照，
    GLuint programId = createGLProgram(colorGouraudVertFile, colorGouraudFragFile);
    GLuint programId2 = createGLProgram(lightCubeVertFile, lightCubeFragFile);

    GLuint VBO;
    GLuint containerVAO;

    glGenVertexArrays(1, &containerVAO);
    glBindVertexArray(containerVAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_normal_vertices), color_normal_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // 光照体
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    while (!glfwWindowShouldClose(pWindow)) {
        GLfloat currentFrame = (GLfloat) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        processInput(pWindow);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 1、目前，我们的光源时静止的，你可以尝试使用sin和cos函数让光源在场景中来回移动，此时再观察光照效果能让你更容易理解冯氏光照模型。
        // change the light's position values over time (can be done anywhere in the render loop actually, but try to do it at least before using the light source positions)
        colorLightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
        colorLightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
        // 1、
        glUseProgram(programId);
        GLint objectColorLoc = glGetUniformLocation(programId, "objectColor");
        GLint lightColorLoc = glGetUniformLocation(programId, "lightColor");
        GLint lightPosLoc = glGetUniformLocation(programId, "lightPos");
        GLint viewPosLoc = glGetUniformLocation(programId, "viewPos");
        glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f); // 我们所熟悉的珊瑚红
        glUniform3f(lightColorLoc, 1.0f, 0.5f, 1.0f); // 依旧把光源设置为白色
        glUniform3f(lightPosLoc, colorLightPos.x, colorLightPos.y, colorLightPos.z);
        glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);

        glm::mat4 view;
        glm::mat4 projection;
        view = camera.GetViewMatrix();
        projection = glm::perspective(camera.Zoom, (GLfloat) SRC_HEIGHT / (GLfloat) SRC_WIDTH, 0.1f, 100.f);

        GLint modelLoc = glGetUniformLocation(programId, "model");
        GLint viewLoc = glGetUniformLocation(programId, "view");
        GLint projectionLoc = glGetUniformLocation(programId, "projection");

        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(containerVAO);
        glm::mat4 model;
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // 2、
        glUseProgram(programId2);
        modelLoc = glGetUniformLocation(programId2, "model");
        viewLoc = glGetUniformLocation(programId2, "view");
        projectionLoc = glGetUniformLocation(programId2, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        model = glm::mat4();
        model = glm::translate(model, colorLightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        // Draw the light object (using light's vertex attributes)
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // swap 数据
        glfwSwapBuffers(pWindow);
    }

    glDisable(GL_DEPTH_TEST);
    glDeleteVertexArrays(1, &containerVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(programId);
    glDeleteProgram(programId2);

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();

    return 0;
}

void GLColor::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void GLColor::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll((GLfloat) yoffset);
}

void GLColor::mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = (GLfloat) xpos;
        lastY = (GLfloat) ypos;
        firstMouse = false;
    }

    GLfloat xoffset = (GLfloat) xpos - lastX;
    GLfloat yoffset = lastY - (GLfloat) ypos; // Reversed since y-coordinates go from bottom to left

    lastX = (GLfloat) xpos;
    lastY = (GLfloat) ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}