#pragma once
#include <SOIL/SOIL.h>
#define GLEW_STATIC
#include "ShaderInterface.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>


using namespace std;

enum Texture_Type{
	TX_TEXTURE,
	TX_SKYBOX
};


class TextureLoader
{
private:
	GLuint _textureLoaderID;
	Texture_Type _type;

	void loadTexture(char* location);
	void loadSkybox();

	GLuint loadCubemap(vector<const GLchar*> faces);

public:
	GLuint getTextureLoaderID();
	void createTexture(ShaderInterface* shader);

	Texture_Type getTextureType();

	TextureLoader(char* location, Texture_Type type);
	~TextureLoader();


};

