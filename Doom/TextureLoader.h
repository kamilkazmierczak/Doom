#pragma once
#include <SOIL/SOIL.h>
#define GLEW_STATIC
#include "ShaderInterface.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class TextureLoader
{
private:
	GLuint _textureLoaderID;

public:
	GLuint getTextureLoaderID();
	void createTexture(ShaderInterface* shader);

	TextureLoader(char* location);
	~TextureLoader();

};

