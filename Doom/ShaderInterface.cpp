#include "ShaderInterface.h"
#include <stdio.h> //DEL?
#include <stdlib.h>//DEL?

GLuint ShaderInterface::getProgramHandle()
{
	//nie da sie w moim Shader class
	return NULL;
}

GLint ShaderInterface::get_aPositionVertex()
{
	return _aPositionVertex;
}

GLint ShaderInterface::get_uColor()
{
	return _uColor;
}

GLint ShaderInterface::getUniformLocation(char* name)
{
	return glGetUniformLocation(shader->Program, name);
}



ShaderInterface::ShaderInterface(const GLchar *VS, const GLchar *FS)
{
	shader = new Shader(VS, FS);

	_aPositionVertex = glGetAttribLocation(shader->Program, "aPositionVertex");
	_uColor = glGetUniformLocation(shader->Program, "uColor");
}


ShaderInterface::~ShaderInterface()
{
	//delete shader; //DANGER (moze nie funkcjonowac poprawnie z moim Shader.h
}

char *ShaderInterface::loadTextFromFile(char* file) //DEL?
{
	/*
	FILE* currentFile = fopen(file, "rt");
	fseek(currentFile, 0, SEEK_END);
	int count = (int)ftell(currentFile);
	rewind(currentFile);
	char *data = (char*)malloc(sizeof(char)*(count + 1));
	count = (int)fread(data, sizeof(char), count, currentFile);
	data[count] = '\0';

	fclose(currentFile);

	return data;
	*/
	return NULL;
}

void ShaderInterface::use()
{
	shader->Use();
}