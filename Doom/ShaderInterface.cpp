#include "ShaderInterface.h"
#include <stdio.h> 
#include <stdlib.h>


GLint ShaderInterface::get_aPositionVertex()
{
	return _aPositionVertex;
}

GLint ShaderInterface::get_aPositionNormal()
{
	return _aPositionNormal;
}

GLint ShaderInterface::get_aTextureCoord()
{
	return _aTextureCoord;
}

GLint ShaderInterface::get_uColor()
{
	return _uColor;
}

GLint ShaderInterface::get_uLightPosition()
{
	return _uLightPosition;
}

GLint ShaderInterface::get_uLightPosition2()
{
	return _uLightPosition2;
}


GLint ShaderInterface::getUniformLocation(char* name)
{
	return glGetUniformLocation(shader->Program, name);
}



ShaderInterface::ShaderInterface(const GLchar *VS, const GLchar *FS)
{
	shader = new Shader(VS, FS);

	_aPositionVertex = glGetAttribLocation(shader->Program, "aPositionVertex");
	_aPositionNormal = glGetAttribLocation(shader->Program, "aPositionNormal");
	_aTextureCoord = glGetAttribLocation(shader->Program, "aTextureCoord");

	_uColor = glGetUniformLocation(shader->Program, "uColor");
	_uLightPosition = glGetUniformLocation(shader->Program, "uLightPosition");
	_uLightPosition2 = glGetUniformLocation(shader->Program, "uLightPosition2");
}


ShaderInterface::~ShaderInterface()
{
	//delete shader;
}


void ShaderInterface::use()
{
	shader->Use();
}

Shader* ShaderInterface::getShader()
{
	return shader;
}