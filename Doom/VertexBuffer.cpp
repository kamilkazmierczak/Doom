#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const GLvoid *data, 
						   GLsizeiptr size, 
						   GLenum mode, 
						   GLsizei count, 
						   GLsizei stride, 
						   ShaderInterface *shader,
						   ShaderData *shaderData,
						   GLvoid *positionOffset,
						   GLvoid *normalOffset,
						   GLvoid *textureOffset,
						   TextureLoader *textureLoader)
:_mode(mode), _count(count), _stride(stride), _shader(shader), _positionOffset(positionOffset), _normalOffset(normalOffset),
_textureOffset(textureOffset), _shaderData(shaderData), _textureLoader(textureLoader)
{
	glGenBuffers(1, &_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0); //??
	configureVertexAttributes(); //nie do konca jestem pewien czy to tu powinno byc, ale dziala
								//nie moze byc w petli bo sie wykrzaczy
}


VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_vertexBufferID);
	_vertexBufferID = 0;
}

GLuint VertexBuffer::getVertexBufferID()
{
	return _vertexBufferID;
}


ShaderInterface* VertexBuffer::getShader()
{
	return _shader;
}

ShaderData* VertexBuffer::getShaderData()
{
	return _shaderData;
}

TextureLoader* VertexBuffer::getTextureLoader()
{
	return _textureLoader;
}

void VertexBuffer::configureVertexAttributes()
{
		glGenVertexArrays(1, &VAO);

		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);//zeby bral wlasciwe wierzcholki
		glBindVertexArray(VAO);

		if (_shader->get_aPositionVertex() != -1)
		{
			glEnableVertexAttribArray(_shader->get_aPositionVertex());
			glVertexAttribPointer(_shader->get_aPositionVertex(), 3, GL_FLOAT, GL_FLOAT, _stride, _positionOffset);
		}

		if (_shader->get_aPositionNormal() != -1)
		{
			glEnableVertexAttribArray(_shader->get_aPositionNormal());
			glVertexAttribPointer(_shader->get_aPositionNormal(), 3, GL_FLOAT, GL_FLOAT, _stride, _normalOffset);
		}

		if (_shader->get_aTextureCoord() != -1)
		{
			glEnableVertexAttribArray(_shader->get_aTextureCoord());
			glVertexAttribPointer(_shader->get_aTextureCoord(), 3, GL_FLOAT, GL_FLOAT, _stride, _textureOffset);
		}

		glBindVertexArray(0);
}


void VertexBuffer::renderVertexBuffer()
{	
	if (_textureLoader != NULL)
		_textureLoader->createTexture(_shader);
	
	

	glBindVertexArray(VAO);
	glDrawArrays(_mode, 0, _count);
	glBindVertexArray(0);
	
}