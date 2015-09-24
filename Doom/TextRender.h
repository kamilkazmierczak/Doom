#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H  
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "Constants.h"
#include <GLFW/glfw3.h>


using namespace std;


struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};



class TextRender
{
private:
	GLuint _VAO, _VBO;
	Shader *_shader;

	map<GLchar, Character> Characters;

	void configShader();
	void configText();

	TextRender();
	~TextRender();

public:
	void renderText(string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	static TextRender& getTextRender();
	static void destroyTextRender();
};

