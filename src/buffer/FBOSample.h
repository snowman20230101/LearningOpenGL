//
// Created by windy on 2022/8/9.
//

#ifndef LEARNINGOPENGL_FBOSAMPLE_H
#define LEARNINGOPENGL_FBOSAMPLE_H

#include "Base.h"

#define fboSampleVertexFile "buffer/fbo_sample_vertex.glsl"
#define fboSampleFragmentFile "buffer/fbo_sample_fragment.glsl"

#define fboSampleScreenVertexFile "buffer/fbo_sample_screen_vertex.glsl"
#define fboSampleScreenFragmentFile "buffer/fbo_sample_screen_fragment.glsl"

class FBOSample : public Base {
public:
    FBOSample();

    ~FBOSample() override;

    int execute() override;

    void processInput(GLFWwindow *window) override;

    static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

    static void mouseCallback(GLFWwindow *window, double xpos, double ypos);

protected:
    // This function loads a texture from file. Note: texture loading functions like these are usually
    // managed by a 'Resource Manager' that manages all resources (like textures, models, audio).
    // For learning purposes we'll just define it as a utility function.
    GLuint loadTexture(const char *path, GLboolean alpha = GL_FALSE);

    /**
     * Generates a texture that is suited for attachments to a framebuffer
     *
     * @param depth
     * @param stencil
     * @return
     */
    GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);

protected:
    // Set the object data (buffers, vertex attributes)
    GLfloat cubeVertices[180] = {
            // Positions          // Texture Coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };
    GLfloat floorVertices[30] = {
            // Positions          // Texture Coords (note we set these higher than 1 that together with GL_REPEAT as texture wrapping mode will cause the floor texture to repeat)
            5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
            -5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

            5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
            -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
            5.0f, -0.5f, -5.0f, 2.0f, 2.0f
    };
    GLfloat quadVertices[24] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
            // Positions   // TexCoords
            -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f
    };

};


#endif //LEARNINGOPENGL_FBOSAMPLE_H
