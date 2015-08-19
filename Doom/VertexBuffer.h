#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

class VertexBuffer
{
private:
	GLuint _vertexBufferID;
	GLenum _mode;
	GLsizei _count; //do liczenia wierzczholkow (w sensie trojkat =3 ) //dla glDrawArrays
	GLsizei _stride; //rozmiar wszystkich atrybutow (chyba) (chodzi i VAO)(chyba)
	GLuint VAO;

public:

	GLuint getVertexBufferID();

	VertexBuffer(const GLvoid *data, GLsizeiptr size, GLenum mode, GLsizei count, GLsizei stride);
	~VertexBuffer();

	void configureVertexAttributes(GLint vertexPosition);//vertexPosiotion to layout (location = 0) //0
	void renderVertexBuffer();
};
