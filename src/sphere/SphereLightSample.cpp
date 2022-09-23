//
// Created by windy on 2022/8/11.
//

#include "SphereLightSample.h"
#include "Sphere.h"

// 光照
glm::vec3 sphereLightPos(0.6f, 0.5f, 1.0f);

SphereLightSample::SphereLightSample() {
    std::cout << "SphereLightSample::~SphereLightSample()" << std::endl;
}

SphereLightSample::~SphereLightSample() {
    std::cout << "SphereLightSample::~SphereLightSample()" << std::endl;
}

int SphereLightSample::execute() {
    std::cout << "SphereLightSample::execute()" << std::endl;

    createWindow();

    GLuint programId = createGLProgram(sphereLightSampleVertexFile, sphereLightSampleFragmentFile);

    Sphere mySphere1(30);
    std::vector<int> ind = mySphere1.getIndices(); // 球体点的标注
    std::vector<glm::vec3> vert = mySphere1.getVertices(); // 球上的顶点
    std::vector<glm::vec2> tex = mySphere1.getTexCoords(); // 纹理坐标
    std::vector<glm::vec3> norm = mySphere1.getNormals(); // 球上法向量

    std::vector<float> sphereVertices; // 球体顶点

    int numIndices = mySphere1.getNumIndices();
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

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(GLfloat), &sphereVertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    std::string fileName = string(ROOT_DIR) + "resources/textures/earth.jpeg";
    unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    while (!glfwWindowShouldClose(pWindow)) {
        glfwPollEvents();
        processInput(pWindow);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元，TODO 默认就是第一个纹理单元，如果是一个纹理采样，就可以不用写这个代码也行。
        glBindTexture(GL_TEXTURE_2D, texture);

        glUseProgram(programId);

        // 光照处理
        GLint objectColorLoc = glGetUniformLocation(programId, "objectColor");
        GLint lightColorLoc = glGetUniformLocation(programId, "lightColor");
        GLint lightPosLoc = glGetUniformLocation(programId, "lightPos");
        GLint viewPosLoc = glGetUniformLocation(programId, "viewPos");
        glUniform3f(objectColorLoc, 1.0f, 1.0f, 0.0f); // 我们所熟悉的珊瑚红
        glUniform3f(lightColorLoc, 1.0f, 0.5f, 1.0f); // 依旧把光源设置为白色
        glUniform3f(lightPosLoc, sphereLightPos.x, sphereLightPos.y, sphereLightPos.z);
        glUniform3f(viewPosLoc, 1.0f, 1.0f, 0.4f);

        glm::mat4 model = glm::mat4(1.0);
        glm::mat4 view;
        glm::mat4 projection;
        // 旋转
        model = glm::rotate(model, (GLfloat) glfwGetTime() * glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.1f));

        // 位移
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

        // 投影矩阵
        projection = glm::perspective(glm::radians(270.0f), (GLfloat) SRC_WIDTH / (GLfloat) SRC_HEIGHT, 0.1f, 100.0f);

        glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // 开启面剔除(只需要展示一个面，否则会有重合)
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glDepthFunc(GL_LEQUAL);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, numIndices);
        glBindVertexArray(0);

        glfwSwapBuffers(pWindow);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(programId);

    glfwTerminate();

    return 0;
}