#pragma once
#include "Shader.h"
#include <iostream>
class ShaderInterface
{
private:

	Shader *shader;

	GLint _aPositionVertex; 
	GLint _aPositionNormal;
	GLint _aTextureCoord;
	GLint _uColor;
	GLint _uLightPosition;

public:

	GLint get_aPositionVertex();
	GLint get_aPositionNormal();
	GLint get_aTextureCoord();

	GLint get_uColor();
	GLint get_uLightPosition();
	GLint getUniformLocation(char* name);

	Shader* getShader();

	void use();

	ShaderInterface(const GLchar* VS, const GLchar* FS);
	~ShaderInterface();
};

