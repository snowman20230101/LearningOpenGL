//
// Created by windy on 2022/8/8.
// 文字绘制（通过freeType）
//

#ifndef LEARNINGOPENGL_CHARACTERSSAMPLE_H
#define LEARNINGOPENGL_CHARACTERSSAMPLE_H

#include "Base.h"
#include <freetype2/ft2build.h>
#include <freetype2/freetype/freetype.h>
#include FT_FREETYPE_H
#include <freetype/ftglyph.h>

#define charactersVertexFile "characters/characters_vertex.glsl"
#define charactersFragmentFile "characters/characters_fragment.glsl"

class CharactersSample : public Base {

public:
    CharactersSample();

    ~CharactersSample() override;

    int execute() override;

private:

    /**
     * ascii码
     */
    static void loadFaceByAscii();

    /**
     * unicode码
     *
     * @param text
     * @param textLen
     */
    static void loadFaceByUnicode(const wchar_t *text, int textLen);

//    static int getTextLen(const wchar_t tc[]) {
//        int arrLen = sizeof(tc);
//        int once = sizeof(tc[0]);
//        return arrLen / once - 1;
//    }

    void renderText(GLuint programId, std::string text,
                    GLfloat x, GLfloat y, GLfloat scale, const glm::vec3 &color) const;

    void renderTextWChar(GLuint programId, const wchar_t *text, int textLen,
                         GLfloat x, GLfloat y, GLfloat scale, const glm::vec3 &color) const;

private:
    GLuint VBO = GL_NONE;
    GLuint VAO = GL_NONE;
    GLint textLoc = GL_NONE;
};


#endif //LEARNINGOPENGL_CHARACTERSSAMPLE_H
