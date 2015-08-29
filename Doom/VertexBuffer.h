#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderInterface.h"
#include "ShaderData.h"
#include "TextureLoader.h"
#include <iostream>
using namespace std;

class VertexBuffer
{
private:
	GLuint _vertexBufferID;
	ShaderInterface *_shader;
	ShaderData *_shaderData;
	TextureLoader *_textureLoader;
	GLenum _mode;
	GLsizei _count; //do liczenia wierzczholkow (w sensie trojkat =3 ) //dla glDrawArrays
	GLsizei _stride; // dla VAO
	GLuint VAO;
	GLvoid *_positionOffset;
	GLvoid *_normalOffset;
	GLvoid *_textureOffset;

public:

	GLuint getVertexBufferID();
	ShaderInterface *getShader();
	ShaderData *getShaderData();

	VertexBuffer(const GLvoid *data, 
				GLsizeiptr size, 
				GLenum mode, 
				GLsizei count, 
				GLsizei stride, 
				ShaderInterface *shader,
				ShaderData *shaderData,
				GLvoid *_positionOffset,
				GLvoid *_normalOffset,
				GLvoid *_textureOffset,
				TextureLoader *textureLoader);
	~VertexBuffer();

	void configureVertexAttributes();//vertexPosiotion to layout (location = 0) //0
	void renderVertexBuffer();
};

