#pragma once
#include "Shader.h"
#include <iostream>
class ShaderInterface
{
private:

	//Ta klasa siê raczej do niczego nie przyda bo shadery mam ró¿ne i maj¹ ró¿ne atrybuty
	//

	Shader *shader;

	GLint _aPositionVertex; //position (tutorial)
	GLint _uColor; //to  tyczy sie fragment shadera ale tylko "tego jednego"

	char* _vertexShaderString;  //DEL?
	char* _fragmentShaderString; //DEL?

	char *loadTextFromFile(char *file);  //DEL?


public:

	GLuint getProgramHandle();
	GLint get_aPositionVertex();
	GLint get_uColor();
	void use();
	GLint getUniformLocation(char* name);

	ShaderInterface(const GLchar* VS, const GLchar* FS); //WARNING on mial char i specjalna funkcje do wczytywania tekstu co ominalem
	~ShaderInterface();
};

