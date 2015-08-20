#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderInterface.h"
#include <iostream>
using namespace std;

class VertexBuffer
{
private:
	GLuint _vertexBufferID;
	ShaderInterface *_shader;
	GLenum _mode;
	GLsizei _count; //do liczenia wierzczholkow (w sensie trojkat =3 ) //dla glDrawArrays
	GLsizei _stride; //rozmiar wszystkich atrybutow (chyba) (chodzi i VAO)(chyba)
	GLuint VAO;

public:

	GLuint getVertexBufferID();
	ShaderInterface *getShader();

	VertexBuffer(const GLvoid *data, GLsizeiptr size, GLenum mode, GLsizei count, GLsizei stride, ShaderInterface *shader);
	~VertexBuffer();

	void configureVertexAttributes();//vertexPosiotion to layout (location = 0) //0
	void renderVertexBuffer();
};

