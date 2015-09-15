#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderInterface.h"
#include "ShaderData.h"
#include "TextureLoader.h"
#include <glm/glm.hpp>
#include <iostream>
using namespace std;
using namespace glm;

struct ThreeVertices
{
	vec3 a;
	vec3 b;
	vec3 c;
};

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

	//do detekcji kolizji
	vector <ThreeVertices> *_myVertices;
	vector <ThreeVertices> *_myRealVertices;
	void loadVertices(GLvoid *table, GLsizeiptr size, GLsizeiptr dataSize);

	


public:

	vector <ThreeVertices>* getRealVertices();

	GLuint getVertexBufferID();
	ShaderInterface *getShader();
	ShaderData *getShaderData();
	TextureLoader *getTextureLoader();


	VertexBuffer(GLvoid *data, 
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


	void loadRealVertices(mat4& model);
	void configureVertexAttributes();//vertexPosiotion to layout (location = 0) //0
	void renderVertexBuffer();
};

