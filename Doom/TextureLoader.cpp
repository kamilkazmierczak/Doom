#include "TextureLoader.h"
#include <iostream>

using namespace std;

TextureLoader::TextureLoader(char* location)
{
	glGenTextures(1, &_textureLoaderID);
	glBindTexture(GL_TEXTURE_2D, _textureLoaderID); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(location, &width, &height, 0, SOIL_LOAD_RGB);
	
	//nie wiem czy tak jest (chyba) nie moge znalezc nigdzie dokumentacji SOIL, ale ma to sens (*)
	if (image == NULL)
		cout << "Nie udalo sie zaladowac tekstury" << endl;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

}

void TextureLoader::createTexture(ShaderInterface* shader)
{
	//to chyba mozna inkrementowac zeby po kolejnych teksturach lecial (gdyby byly)
	//GL_TEXTURE0 + i

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _textureLoaderID);
		glUniform1i(shader->getUniformLocation("uTexture1"), 0);
}


GLuint TextureLoader::getTextureLoaderID()
{
	return _textureLoaderID;
}

TextureLoader::~TextureLoader()
{	//Nie testowane
	/*
	glDeleteTextures(1, &_textureLoaderID);
	_textureLoaderID = 0;
	*/
}




