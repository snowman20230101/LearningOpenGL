//
// Created by windy on 2022/8/10.
// 球体类
//

#ifndef LEARNINGOPENGL_SPHERE_H
#define LEARNINGOPENGL_SPHERE_H

#include "CommonInclude.h"
#include <vector>

class Sphere {
public:
    /**
     *
     */
    Sphere();

    /**
     *
     * @param prec
     */
    explicit Sphere(int prec);

    /**
     *
     * @return
     */
    int getNumVertices() const;

    /**
     *
     *
     * @return
     */
    int getNumIndices() const;

    /**
     * 顶点数量
     *
     * @return
     */
    std::vector<int> getIndices();

    /**
     * 顶点向量
     *
     * @return
     */
    std::vector<glm::vec3> getVertices();

    /**
     * 纹理坐标向量
     *
     * @return
     */
    std::vector<glm::vec2> getTexCoords();

    /**
     * 法线向量
     *
     * @return
     */
    std::vector<glm::vec3> getNormals();

private:
    //
    int numVertices{0};
    //
    int numIndices{0};
    //
    std::vector<int> indices;
    // 顶点
    std::vector<glm::vec3> vertices;
    // 纹理
    std::vector<glm::vec2> texCoords;
    // 法线
    std::vector<glm::vec3> normals;

    /**
     *
     */
    void init(int);

    /**
     *
     *
     * @param degrees
     * @return
     */
    static float toRadians(float degrees);
};


#endif //LEARNINGOPENGL_SPHERE_H
