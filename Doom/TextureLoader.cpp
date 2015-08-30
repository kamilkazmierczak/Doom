#include "TextureLoader.h"




TextureLoader::TextureLoader(char* location, Texture_Type type) :_type(type)
{
	if (_type == TX_TEXTURE)
		loadTexture(location);

	if (_type == TX_SKYBOX)
		loadSkybox();
}

void TextureLoader::loadTexture(char* location)
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

void TextureLoader::loadSkybox()
{
	vector<const GLchar*> faces;
	
	/*
	faces.push_back("skybox/water/right.jpg");
	faces.push_back("skybox/water/left.jpg");
	faces.push_back("skybox/water/top.jpg");
	faces.push_back("skybox/water/bottom.jpg");
	faces.push_back("skybox/water/back.jpg");
	faces.push_back("skybox/water/front.jpg");
	*/

	faces.push_back("skybox/endless_sky/endless_rt.jpg");
	faces.push_back("skybox/endless_sky/endless_lf.jpg");
	faces.push_back("skybox/endless_sky/endless_up.jpg");
	faces.push_back("skybox/endless_sky/endless_dn.jpg");
	faces.push_back("skybox/endless_sky/endless_bk.jpg");
	faces.push_back("skybox/endless_sky/endless_ft.jpg");
	

	_textureLoaderID = loadCubemap(faces);
}


GLuint TextureLoader::loadCubemap(vector<const GLchar*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
			);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}


void TextureLoader::createTexture(ShaderInterface* shader)
{
	//to chyba mozna inkrementowac zeby po kolejnych teksturach lecial (gdyby byly)
	//GL_TEXTURE0 + i

	if (_type == TX_TEXTURE)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _textureLoaderID);
		glUniform1i(shader->getUniformLocation("uTexture1"), 0);
	}

	if (_type == TX_SKYBOX)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _textureLoaderID); 
		glUniform1i(shader->getUniformLocation("skybox"), 0); //assign a location value to the texture sampler
	}
		
}


GLuint TextureLoader::getTextureLoaderID()
{
	return _textureLoaderID;
}

Texture_Type TextureLoader::getTextureType()
{
	return _type;
}

TextureLoader::~TextureLoader()
{	//Nie testowane
	/*
	glDeleteTextures(1, &_textureLoaderID);
	_textureLoaderID = 0;
	*/
}



