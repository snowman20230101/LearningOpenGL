//
// Created by windy on 2022/7/12.
// 通过 一个 VAO VBO 画两个三角心
// 练习题：添加更多顶点到数据中，使用glDrawArrays，尝试绘制两个彼此相连的三角形
//

#include "TriangleExercises_1.h"

TriangleExercises_1::TriangleExercises_1() = default;

TriangleExercises_1::~TriangleExercises_1() = default;

int TriangleExercises_1::execute() {
    std::cout << "TriangleExercises_1 execute()" << std::endl;
    createWindow();

    unsigned int programId = createGLProgram(triangleVertexFile, triangleFragmentFile);

    unsigned int VBO;
    unsigned int VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexIds), vertexIds, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *) nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(pWindow)) {
        processInput(pWindow);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programId);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(programId);

    glfwTerminate();

    return 0;
}
