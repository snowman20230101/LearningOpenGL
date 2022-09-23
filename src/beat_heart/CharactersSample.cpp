//
// Created by windy on 2022/8/8.
// 使用FreeType 绘制文字。
//

#include "CharactersSample.h"

#include <map>

static const wchar_t BYTE_TEXT[] = L"微信公众号字节流动，欢迎关注交流学习。";
static const int MAX_SHORT_VALUE = 65536;

/// Holds all state information relevant to a character as loaded using FreeType
// 字符定义
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture 字符纹理
    glm::ivec2 Size;    // Size of glyph // 字符大小
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
};

std::map<GLchar, Character> charactersMap;

CharactersSample::CharactersSample() {
    std::cout << "CharactersSample::CharactersSample()" << std::endl;
}

// noexcept
CharactersSample::~CharactersSample() {
    std::cout << "CharactersSample::~CharactersSample()" << std::endl;
}

int CharactersSample::execute() {
    std::cout << "CharactersSample::execute()" << std::endl;

    createWindow();

    // Set OpenGL options
    glEnable(GL_CULL_FACE);
    // 当然我们必需开启混合才能让这一切行之有效：
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint programId = createGLProgram(charactersVertexFile, charactersFragmentFile);

    // 预备
    loadFaceByAscii();
    loadFaceByUnicode(BYTE_TEXT, sizeof(BYTE_TEXT) / sizeof(BYTE_TEXT[0]) - 1);

    // 至于投影矩阵我们将使用一个正交投影矩阵。对于文字渲染我们通常都不需要进行透视，使用正交投影也能保证我们所有的顶点坐标设置有效：
    glm::mat4 projection = glm::ortho(0.0f, (GLfloat) SRC_WIDTH, 0.0f, (GLfloat) SRC_HEIGHT);
    glUseProgram(programId);
    glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    textLoc = glGetUniformLocation(programId, "text");

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 每个2D方块需要6个顶点，每个顶点又是由一个4维向量（一个纹理坐标和一个顶点坐标）组成
    // 由于我们会在绘制字符时更新这断内存，所以我们将内存类型设置为 GL_DYNAMIC_DRAW
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    // 解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(pWindow)) {
        // Check and call events
        glfwPollEvents();

        processInput(pWindow);
        // Clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        std::string text = "This is sample text";
        std::string text2 = "hello World! OpenGL Learning";

        renderText(programId, text, 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        renderText(programId, text2, 25.0f, 100.0f, 0.99999f, glm::vec3(0.3, 0.7f, 0.9f));

        renderTextWChar(programId,
                        BYTE_TEXT,
                        sizeof(BYTE_TEXT) / sizeof(BYTE_TEXT[0]) - 1,
                        25.0f,
                        170.0f,
                        1.0f,
                        glm::vec3(1.0f, 0.0f, 0.0f)
        );

        glfwSwapBuffers(pWindow);
    }

    glfwTerminate();

    return 0;
}

void CharactersSample::renderText(GLuint programId, std::string text,
                                  GLfloat x, GLfloat y, GLfloat scale, const glm::vec3 &color) const {
    glUseProgram(programId);
    glUniform3f(glGetUniformLocation(programId, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // 对文本中的所有字符迭代
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = charactersMap[*c];

        GLfloat xpos = x + (GLfloat) ch.Bearing.x * scale;
        GLfloat ypos = y - (GLfloat) (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = (GLfloat) ch.Size.x * scale;
        GLfloat h = (GLfloat) ch.Size.y * scale;
        // 当前字符的VBO
        GLfloat vertices[6][4] = {
                {xpos,     ypos + h, 0.0, 0.0},
                {xpos,     ypos,     0.0, 1.0},
                {xpos + w, ypos,     1.0, 1.0},

                {xpos,     ypos + h, 0.0, 0.0},
                {xpos + w, ypos,     1.0, 1.0},
                {xpos + w, ypos + h, 1.0, 0.0}
        };
        glActiveTexture(GL_TEXTURE0);
        // 在方块上绘制字形纹理
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glUniform1i(textLoc, 0);
        // 更新当前字符的VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // 绘制方块
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // 更新位置到下一个字形的原点，注意单位是1/64像素
        x += (GLfloat) (ch.Advance >> 6) * scale; //(2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void CharactersSample::renderTextWChar(GLuint programId, const wchar_t *text, int textLen,
                                       GLfloat x, GLfloat y, GLfloat scale, const glm::vec3 &color) const {
    glUseProgram(programId);
    glUniform3f(glGetUniformLocation(programId, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

//    glm::vec2 viewport(SRC_WIDTH, SRC_HEIGHT);

//    x *= viewport.x;
//    y *= viewport.y;

    // 对文本中的所有字符迭代
//    std::string::const_iterator c;
    for (int i = 0; i < textLen; i++) {
        Character ch = charactersMap[text[i]];

        GLfloat xpos = x + (GLfloat) ch.Bearing.x * scale;
        GLfloat ypos = y - (GLfloat) (ch.Size.y - ch.Bearing.y) * scale;

//        xpos /= viewport.x;
//        ypos /= viewport.y;

        GLfloat w = (GLfloat) ch.Size.x * scale;
        GLfloat h = (GLfloat) ch.Size.y * scale;

//        w /= viewport.x;
//        h /= viewport.y;

//        printf("CharactersSample::renderTextWChar [xpos,ypos,w,h]=[%f, %f, %f, %f]\n", xpos, ypos, w, h);

        // 当前字符的VBO
        GLfloat vertices[6][4] = {
                {xpos,     ypos + h, 0.0, 0.0},
                {xpos,     ypos,     0.0, 1.0},
                {xpos + w, ypos,     1.0, 1.0},

                {xpos,     ypos + h, 0.0, 0.0},
                {xpos + w, ypos,     1.0, 1.0},
                {xpos + w, ypos + h, 1.0, 0.0}
        };
        glActiveTexture(GL_TEXTURE0);
        // 在方块上绘制字形纹理
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glUniform1i(textLoc, 0);
        // 更新当前字符的VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // 绘制方块
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // 更新位置到下一个字形的原点，注意单位是1/64像素
        x += (GLfloat) (ch.Advance >> 6) * scale; //(2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void CharactersSample::loadFaceByAscii() {
    FT_Library ft;
    FT_Error err;
    err = FT_Init_FreeType(&ft);
    if (err) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library errCode is " << err << std::endl;
    }

    FT_Face face;
    std::string fontStr = std::string(ROOT_DIR) + "resources/fonts/Arial.ttf";
//    std::string fontStr = std::string(ROOT_DIR) + "resources/fonts/Antonio-Regular.ttf";
    err = FT_New_Face(ft, fontStr.c_str(), 0, &face);
    if (err) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

//    FT_Set_Char_Size(face, 2000, 0, 0, 0);
    // 此函数设置了字体面的宽度和高度，将宽度值设为0表示我们要从字体面通过给出的高度中动态计算出字形的宽度。
    FT_Set_Pixel_Sizes(face, 0, 30);

    // 禁用byte-alignment限制
    // 我们想用一个字节来表示纹理颜色，这需要提前通知OpenGL
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte c = 0; c < 128; c++) {
        // 加载字符的字形
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // 生成字形纹理
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // 为每一个字符创建纹理并存储它们的部分度量值。有趣的是我们这里将纹理的格式设置为GL_RED。
        // 通过字形生成的位图是8位灰度图，他的每一个颜色表示为一个字节。
        // 因此我们需要将每一位都作为纹理的颜色值。
        // 我们通过创建每一个字节表示一个颜色的红色分量(颜色分量的第一个字节)来创建字形纹理。
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RED,
                     face->glyph->bitmap.width,
                     face->glyph->bitmap.rows,
                     0,
                     GL_RED,
                     GL_UNSIGNED_BYTE,
                     face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character tempMap = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<GLuint>(face->glyph->advance.x)
        };

        charactersMap.insert(std::pair<GLint, Character>(c, tempMap));
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    // 使用完 字体 释放资源
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void CharactersSample::loadFaceByUnicode(const wchar_t *text, int textLen) {
    FT_Library ft;
    FT_Error err;
    err = FT_Init_FreeType(&ft);
    if (err) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library errCode is " << err << std::endl;
    }

    FT_Face face;
    std::string fontStr = std::string(ROOT_DIR) + "resources/fonts/Arial.ttf";
    err = FT_New_Face(ft, fontStr.c_str(), 0, &face);
    if (err) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    // 此函数设置了字体面的宽度和高度，将宽度值设为0表示我们要从字体面通过给出的高度中动态计算出字形的宽度。
//    FT_Set_Char_Size(face, 50 * 64, 0, 100, 0);
    FT_Select_Charmap(face, ft_encoding_unicode);
    FT_Set_Pixel_Sizes(face, 0, 32);

    //禁用byte-alignment限制
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (int i = 0; i < textLen; i++) {
        // 加载字符的字形
        if (FT_Load_Char(face, FT_Get_Char_Index(face, text[i]), FT_LOAD_DEFAULT)) {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }

        FT_Glyph glyph;
        FT_Get_Glyph(face->glyph, &glyph);

        // Convert the glyph to a bitmap.
        FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph) glyph;

        // This reference will make accessing the bitmap easier
        FT_Bitmap &bitmap = bitmap_glyph->bitmap;

        // 生成字形纹理
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_LUMINANCE,
                     (int) bitmap.width,
                     (int) bitmap.rows,
                     0,
                     GL_LUMINANCE,
                     GL_UNSIGNED_BYTE,
                     bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character tempMap = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<GLuint>((glyph->advance.x / MAX_SHORT_VALUE) << 6)
        };

        charactersMap.insert(std::pair<GLint, Character>(text[i], tempMap));
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    // 使用完 字体 释放资源
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}