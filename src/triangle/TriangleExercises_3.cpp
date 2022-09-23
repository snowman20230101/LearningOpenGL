//
// Created by windy on 2022/7/13.
// 创建两个着色器程序，第二个程序使用与第一个不同的片段着色器，输出黄色；再次绘制这两个三角形，其中一个输出为黄色
// 说白了就是用两个片段着色器程序画两个物体。（这里是三角形）
//

#include "TriangleExercises_3.h"

TriangleExercises_3::TriangleExercises_3() {
    std::cout << "TriangleExercises_3()" << std::endl;
}

TriangleExercises_3::~TriangleExercises_3() {
    std::cout << "~TriangleExercises_3()" << std::endl;
}

int TriangleExercises_3::execute() {
    std::cout << "TriangleExercises_2 execute() sizeof vertexIds is " << sizeof(vertexIds) << std::endl;
    createWindow();

    unsigned int programId = createGLProgram(triangleExercises_3_VertexFile, triangleExercises_3_FragmentFile);
    unsigned int programId2 = createGLProgram(triangleExercises_3_VertexFile, triangleExercises_3_FragmentFile2);

    unsigned int VAO[2];
    unsigned int VBO[2];

    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    // 第一个三角形
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexIds), vertexIds, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid *) nullptr);
    glEnableVertexAttribArray(0);

    // 解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 第二个三角形
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexIds2), vertexIds2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid *) nullptr);
    glEnableVertexAttribArray(0);
    GLint ourColor = glGetUniformLocation(programId2, "ourColor");

    // 解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(pWindow)) {
        processInput(pWindow);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programId);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(programId2);

        // 这里动态修改了片元着色器，TODO 使用 Uniform 属性案例
        double timeValue = glfwGetTime();
        // 首先我们通过glfwGetTime()获取运行的秒数。然后我们使用sin函数让颜色在0.0到1.0之间改变，最后将结果储存到greenValue里。
        GLfloat greenValue = (GLfloat) (sin(timeValue) / 2) + 0.5;
        glUniform4f(ourColor, 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteProgram(programId);

    glfwTerminate();

    return 0;
}
